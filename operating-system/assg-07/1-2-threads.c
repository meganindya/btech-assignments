/* @Mega328p */

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <string.h>


int pin_thread_to_core(int);

void *thread1(void *);
void *thread2(void *);



int n = 10;
int x = 0, k1 = 0, k2 = 0;

int ncores, free_core = 0;
int flag[2], turn;



int main(int argc, char *argv[]) {
    printf("\n");
    if(argc > 1)    n = atoi(argv[1]);
    ncores = sysconf(_SC_NPROCESSORS_ONLN);

    memset((void*) flag, 0, 2);

    clock_t begin = clock();

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    clock_t end   = clock();
    double time_s = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("\nExecution time : %lf\n\n", time_s);

    pthread_exit(0);
}


void *thread1(void *t) {
    if(!pin_thread_to_core(free_core))
    free_core = (free_core + 1) % ncores;

    while(x < n) {
        flag[1] = 1;
        turn = 0;

        while(flag[0] == 1 && turn == 0);

        k1++;
        x += 1;
        printf("k1 : %d,   k2 : %d,   x : %d\n",
            k1, k2, x);

        flag[1] = 0;
    }

    pthread_exit(0);
}

void *thread2(void *t) {
    if(!pin_thread_to_core(free_core))
    free_core = (free_core + 1) % ncores;
    
    while(x < n) {
        flag[0] = 1;
        turn = 1;

        while(flag[1] == 1 && turn == 1);

        k2++;
        x += 2;
        printf("k1 : %d,   k2 : %d,   x : %d\n",
            k1, k2, x);

        flag[0] = 0;
    }

    pthread_exit(0);
}



int pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(
        current_thread, sizeof(cpu_set_t), &cpuset);
}