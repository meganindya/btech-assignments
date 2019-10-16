#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define FILLED      0
#define READY       1
#define NOTREADY    -1


struct memory {
	char buff[100];
	int status,
        pid1,
        pid2;
};



struct memory* shmptr;


// handler function to print message received from USER 2
void handler(int signum) {
	// if signum is SIGUSR1, then USER 1 has received a message from USER 2
	if (signum == SIGUSR1) {
		printf("Received from USER 2: ");
		puts(shmptr -> buff);
	}
}


// main function
int main() {
	int shmid;

	// key value of shared memory
	int key = 12345;

	// shared memory create
	shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666);

	// attaching the shared memory
	shmptr = (struct memory*) shmat(shmid, NULL, 0);


	// store the process id of USER 1 in shared memory
	shmptr -> pid1   = getpid();
	shmptr -> status = NOTREADY;


	// calling the signal function using signal type SIGUSR1
	signal(SIGUSR1, handler);

	while (1) {
		while (shmptr -> status != READY);

		// taking input from USER 1
        sleep(1);
		printf("USER 1: ");
		fgets(shmptr -> buff, 100, stdin);

		shmptr -> status = FILLED;


		// sending message to USER 2
		kill(shmptr -> pid2, SIGUSR2);
	}

	shmdt((void*) shmptr);
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}