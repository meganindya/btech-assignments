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


// handler function to print message received from USER 1
void handler(int signum) {
	// if signum is SIGUSR2, then USER 2 has received a message from USER 1
	if (signum == SIGUSR2) {
		printf("Received from USER 1: ");
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


	// store the process id of USER 2 in shared memory
	shmptr -> pid2   = getpid();
	shmptr -> status = NOTREADY;


	// calling the signal function using signal type SIGUSR2
	signal(SIGUSR2, handler);

	while (1) {
		// taking input from USER 2
        sleep(1);
		printf("USER 2: ");
		fgets(shmptr -> buff, 100, stdin);

		shmptr -> status = READY;


		// sending message to USER 1
		kill(shmptr -> pid1, SIGUSR1);

		while (shmptr -> status == READY);
	}

	shmdt((void*) shmptr);

	return 0;
}