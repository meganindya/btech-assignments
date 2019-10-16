/* @Mega328p */

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <string.h>

#define NTHREADS 4


int pin_thread_to_core(int);

void lock(int);
void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);



int ncores,
    next_core = 0;

int tickets[NTHREADS],
    tselect[NTHREADS];

int n = 10,
    x = 0,
    k[NTHREADS];



int main(int argc, char *argv[]) {
    printf("\n");
    if(argc > 1)    n = atoi(argv[1]);
    ncores = sysconf(_SC_NPROCESSORS_ONLN);

    memset((void*) k, 0, sizeof(k));
    memset((void*) tickets, 0, sizeof(tickets));
	memset((void*) tselect, 0, sizeof(tselect));

    clock_t begin = clock();

    pthread_t thr[NTHREADS];
    pthread_create(&thr[0], NULL,
        thread1, NULL);
    pthread_create(&thr[1], NULL,
        thread2, NULL);
    pthread_create(&thr[2], NULL,
        thread3, NULL);
    pthread_create(&thr[3], NULL,
        thread4, NULL);

    for(int i = 0; i < NTHREADS; i++)
        pthread_join(thr[i], NULL);

    clock_t end   = clock();
    double time_s =
        (double) (end - begin) / CLOCKS_PER_SEC;

    printf("\nExecution time : %lf\n\n", time_s);

    pthread_exit(0);
}


void *thread1(void *t) {
    lock(0);

    if(pin_thread_to_core(0))   return NULL;

    while(x < n) {
        k[0]++;
        x += 1;
        printf("k1 : %d", k[0]);
        for(int i = 1; i < NTHREADS; i++)
            printf(",   k%d : %d", (i + 1), k[i]);
        printf(",   x : %d\n", x);
    }

    tickets[0] = 0;
}

void *thread2(void *t) {
    lock(1);

    if(pin_thread_to_core(1))   return NULL;

    while(x < n) {
        k[1]++;
        x += 2;
        printf("k1 : %d", k[0]);
        for(int i = 1; i < NTHREADS; i++)
            printf(",   k%d : %d", (i + 1), k[i]);
        printf(",   x : %d\n", x);
    }

    tickets[1] = 0;
}

void *thread3(void *t) {
    lock(2);

    if(pin_thread_to_core(2))   return NULL;

    while(x < n) {
        k[2]++;
        x += 3;
        printf("k1 : %d", k[0]);
        for(int i = 1; i < NTHREADS; i++)
            printf(",   k%d : %d", (i + 1), k[i]);
        printf(",   x : %d\n", x);
    }

    tickets[2] = 0;
}

void *thread4(void *t) {
    lock(3);

    if(pin_thread_to_core(3))   return NULL;

    while(x < n) {
        k[3]++;
        x += 4;
        printf("k1 : %d", k[0]);
        for(int i = 1; i < NTHREADS; i++)
            printf(",   k%d : %d", (i + 1), k[i]);
        printf(",   x : %d\n", x);
    }

    tickets[3] = 0;
}

void lock(int tno) { 
    tselect[tno] = 1;

	int max_ticket = 0;

	for(int i = 0; i < NTHREADS; i++) {
		int ticket = tickets[i];
		max_ticket = ticket > max_ticket ? ticket : max_ticket;
	}

	tickets[tno] = max_ticket + 1;

	tselect[tno] = 0;

	for(int i = 0; i < NTHREADS; i++) {
        while(tselect[i]);

		while(tickets[i] != 0 &&
            (tickets[i] < tickets[tno] ||
                (tickets[i] == tickets[tno] &&
                    i < tno)));
	}
}



int pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(
        current_thread, sizeof(cpu_set_t), &cpuset);
}