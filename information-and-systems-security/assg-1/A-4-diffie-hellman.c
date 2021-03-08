#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <math.h>

/*
 * Returns value of a ^ b (mod P).
 */
long long int power(long long int a, long long int b, long long int P)
{
    return b == 1 ? a : (((long long int)pow(a, b)) % P);
}

int main(int argc, char *argv[])
{
    printf("\n");

    long long int P = 23; // prime number P
    printf("Prime Number (P): %lld\n", P);

    long long int G = 9; // primitve root for P, G
    printf("Primitive Root (G): %lld\n\n", G);

    // pipe 1 to send from parent to child
    int fd1[2]; // used to store two ends of pipe 1

    // pipe 2 to send from child to parent
    int fd2[2]; // used to store two ends of pipe 2

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    // parent process
    else if (pid > 0)
    {
        // private key of parent
        long long int a;
        FILE *fp = fopen("A-4-a.txt", "r");
        fscanf(fp, "%lld", &a);
        fclose(fp);

        printf("Private key of process A (a): %lld\n", a);
        // generated key of parent
        long long int x = power(G, a, P), y;
        printf("Generated public key from process A is x = G ^ a (mod P) = %lld\n", x);

        // close reading end of pipe 1
        close(fd1[0]);

        // write x and close writing end of pipe 1
        write(fd1[1], &x, sizeof(x));
        close(fd1[1]);

        // wait for child to send
        wait(NULL);

        // read from child
        read(fd2[0], &y, sizeof(y));

        // secret key for parent
        long long int ka = power(y, a, P);
        printf("Shared secret key at A (ka): %lld\n", ka);

        // close reading end of pipe 2
        close(fd2[0]);

        printf("\n");
        return 0;
    }

    // child process
    else
    {
        // private key of child
        long long int b;
        FILE *fp = fopen("A-4-b.txt", "r");
        fscanf(fp, "%lld", &b);
        fclose(fp);

        printf("Private key of process B (b): %lld\n", b);
        // generated key of child
        long long int x, y = power(G, b, P);
        printf("\nGenerated public key from process B is y = G ^ b (mod P) = %lld\n", y);

        // read from parent
        read(fd1[0], &x, sizeof(x));

        // secret key for child
        long long int kb = power(x, b, P);
        printf("\nShared secret key at B (kb): %lld\n", kb);

        // close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // write y and close writing end of pipe 2
        write(fd2[1], &y, sizeof(y));
        close(fd2[1]);

        exit(0);
    }
}
