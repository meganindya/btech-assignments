#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>

typedef struct matIndex {
    int i, j;
}   indices;

int a[2][2], b[2][2], c[2][2];
int ncores, free_core = 0;

int pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(
        current_thread, sizeof(cpu_set_t), &cpuset);
}

void *multiply(void *arg) {
    pin_thread_to_core((free_core++) % ncores);
    //pin_thread_to_core(0);

    indices *p = (indices *) arg;
    int i = p -> i;
    int j = p -> j;

    c[i][j] = 0;
    for(int k = 0; k < 2; k++)
        c[i][j] += a[i][k] * b[k][j];
}

int main(int argc, char *argv[]) {
    ncores = sysconf(_SC_NPROCESSORS_ONLN);

    a[0][0] = 1;    a[0][1] = 2;
    a[1][0] = 3;    a[1][1] = 4;

    b[0][0] = 1;    b[0][1] = 0;
    b[1][0] = 0;    b[1][1] = 1;

    clock_t begin = clock();

    pthread_t threads[4];
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            indices *temp = (indices *) malloc(sizeof(indices));
            (*temp).i = i;
            (*temp).j = j;
            pthread_create(&threads[i * 2 + j], NULL, multiply, (void *) temp);
        }
    }

    for(int i = 0; i < 4; i++)
        pthread_join(threads[i],  NULL);

    clock_t end   = clock();
    double time_s = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("\nMatrix A :\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++)
            printf("%d\t", a[i][j]);
        printf("\n");
    }

    printf("\nMatrix B :\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }

    printf("\nMatrix A.B :\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++)
            printf("%d\t", c[i][j]);
        printf("\n");
    }

    printf("\nExecution time : %lf\n\n", time_s);

    pthread_exit(0);
}