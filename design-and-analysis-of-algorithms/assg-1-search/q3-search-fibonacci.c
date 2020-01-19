#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>


// pins calling thread to core 0 and sets scheduler scheme to FIFO
int set_thread_affinity() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
    
    struct sched_param prior_param;
    memset(&prior_param, 0, sizeof(struct sched_param));
    prior_param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    sched_setscheduler(0, SCHED_FIFO, &prior_param);
}

// returns time taken to run algorithm
long int get_fibonacci_search_time(int n) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        arr[i] = i;
    
    int key = -1;

    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    int fibM2 = 0, fibM1 = 1;
    int fibM0 = fibM2 + fibM1;

    while (fibM0 < n) {
        fibM2 = fibM1;
        fibM1 = fibM0;
        fibM0 = fibM2 + fibM1;
    }

    int offset = -1;

    while (fibM0 > 1) {
        int i = (offset + fibM2) < (n - 1) ? (offset + fibM2) : (n - 1);

        if (arr[i] < key) {
            fibM0 = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM0 - fibM1;
            offset = i;
        }
        else if (arr[i] > key) {
            fibM0 = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM0 - fibM1;
        }
        else break;
    }

    if (fibM1 == 1 && arr[offset + 1] == key)
        goto exit;
    //============================
    exit:
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);

    // calculating total time taken by the program.
    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken += (end.tv_nsec - start.tv_nsec);
    return time_taken;
}

// driver
int main(int argc, char *argv) {
    // pinning thread to core 0 and setting thread scheduling scheme to FIFO
    set_thread_affinity();

    FILE *fp = fopen("q3-data.csv", "w");

    long int array_sizes[] = {
        10000, 50000, 100000, 300000, 600000, 900000, 1000000, 3000000, 5000000, 7000000, 9000000,
        10000000, 13000000, 17000000, 20000000, 23000000, 27000000, 30000000, 33000000, 37000000, 40000000,
        43000000, 47000000, 50000000, 53000000, 57000000, 60000000, 63000000, 67000000, 70000000, 73000000, 77000000,
        80000000, 83000000, 87000000, 90000000, 93000000, 97000000, 100000000, 103000000, 107000000, 110000000, 113000000, 117000000, 120000000
        };

    int array_length = (int) (sizeof(array_sizes) / sizeof(long int));
    for (int i = 0; i < array_length; i++)
        fprintf(fp, "%ld,%ld\n", array_sizes[i], get_fibonacci_search_time(array_sizes[i]));

    fclose(fp);

    // calling BASH script for plotting
    system("chmod u+x q3-plot.sh");
    system("./q3-plot.sh");

    return 0;
}
