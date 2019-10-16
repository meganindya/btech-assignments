/* @Mega328p */

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>

int sum_even = 0, sum_odd = 0, n = 10;
int ncores, free_core = 0;

int pin_thread_to_core(int core_id) {
   cpu_set_t cpuset;
   CPU_ZERO(&cpuset);
   CPU_SET(core_id, &cpuset);

   pthread_t current_thread = pthread_self();
   return pthread_setaffinity_np(
       current_thread, sizeof(cpu_set_t), &cpuset);
}

void *evenThread(void *t) {
    int core_no = -999;
    if(!pin_thread_to_core(0))
        core_no = 0;
    pid_t tid = syscall(SYS_gettid);
    for(int i = 2; i <= n; i += 2) {
        printf("V : %d\tTID : %d\tCPU : %d\n", i, tid, core_no);
        sum_even += i;
    }
}

void *oddThread(void *t)  {
    int core_no = -999;
    if(!pin_thread_to_core(1))
        core_no = 1;
    pid_t tid = syscall(SYS_gettid);
    for(int i = 1; i <= n; i += 2) {
        printf("V : %d\tTID : %d\tCPU : %d\n", i, tid, core_no);
        sum_odd  += i;
    }
}

int main(int argc, char *argv[]) {
    printf("\n");
    if(argc > 1)    n = atoi(argv[1]);
    ncores = sysconf(_SC_NPROCESSORS_ONLN);

    clock_t begin = clock();

    pthread_t todd, teven;
    pthread_create(&todd,  NULL, oddThread,  NULL);
    pthread_create(&teven, NULL, evenThread, NULL);

    pthread_join(todd,  NULL);
    pthread_join(teven, NULL);

    clock_t end   = clock();
    double time_s = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("\nSum : %d\n", (sum_even + sum_odd));
    printf("\nExecution time : %lf\n\n", time_s);

    pthread_exit(0);
}