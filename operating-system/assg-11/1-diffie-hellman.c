#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>



// returns value of a ^ b mod P
long long int power(long long int a, long long int b, long long int P) {
    if (b == 1)
        return a;

    else
        return (((long long int) pow(a, b)) % P);
}


int main(int argc, char *argv[]) {
	printf("\n");
    long long int P, G, x, a, y, b, ka, kb;  

    P = 23; // prime number P
    printf("Prime Number\t\tP : %lld\n", P);

    G = 9;  // primitve root for P, G
    printf("Primitive Root\t\tG : %lld\n\n", G);


	// pipe 1 to send from parent to child
	int fd1[2]; // used to store two ends of pipe 1

	// pipe 2 to send from child to parent
	int fd2[2]; // used to store two ends of pipe 2

	if (pipe(fd1) == -1 || pipe(fd2) == -1) {
		fprintf(stderr, "Pipe Failed" );
		return 1;
	}


	pid_t pid = fork();
	if (pid < 0) {
		fprintf(stderr, "fork Failed" );
		return 1;
	}

	// parent process
	else if (pid > 0) {
		// private key of parent
        a = 4;
        printf("Parent Private Key\ta  : %lld\n", a);
		// generated key of parent
        x = power(G, a, P);


		// close reading end of pipe 1
		close(fd1[0]);

		// write x and close writing end of pipe 1
        write(fd1[1], &x, sizeof(int));
		close(fd1[1]);


		// wait for child to send
		wait(NULL);


		// read from child
        read(fd2[0], &y, sizeof(int));
		
		// secret key for parent
        ka = power(y, a, P);
        printf("Parent Secret Key\tka : %lld\n", ka);
		
		// close reading end of pipe 2
		close(fd2[0]);

		printf("\n");
		return 0;
	}

	// child process
	else {
		// private key of child
        b = 3;
		printf("Child  Private Key\tb  : %lld\n", b);
		// generated key of child
        y = power(G, b, P);


		// read from parent
        read(fd1[0], &x, sizeof(int));

		// secret key for child
        kb = power(x, b, P);
		printf("Child  Secret Key\tkb : %lld\n", kb);

		// close both reading ends
		close(fd1[0]);
		close(fd2[0]);

		// write y and close writing end of pipe 2
        write(fd2[1], &y, sizeof(int));
		close(fd2[1]);
	}
}
