#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <sys/stat.h>


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


// ================= SELECTION SORT =================
// returns time taken to run algorithm
long int get_selection_sort_time(int n, FILE *fp) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }

        if (arr[i] > arr[min]) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    //============================
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);

    // calculating total time taken by the program.
    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken += (end.tv_nsec - start.tv_nsec);
    return time_taken / 1e6;
}

// ================= INSERTION SORT =================
// returns time taken to run algorithm
long int get_insertion_sort_time(int n, FILE *fp) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    for (int i = 0; i < n; i++) {
        int x = arr[i];
        int j = i - 1;
        while (j > 0 && arr[j] > x) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = x;
    }
    //============================
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);

    // calculating total time taken by the program.
    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken += (end.tv_nsec - start.tv_nsec);
    return time_taken / 1e6;
}

// ================== BUBBLE SORT ==================
// returns time taken to run algorithm
long int get_bubble_sort_time(int n, FILE *fp) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    for (int i = 0; i < n; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }
    //============================
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);

    // calculating total time taken by the program.
    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken += (end.tv_nsec - start.tv_nsec);
    return time_taken / 1e6;
}


// driver
int main(int argc, char *argv) {
    // pinning thread to core 0 and setting thread scheduling scheme to FIFO
    set_thread_affinity();

    // fetch list of sizes
    FILE *fp = fopen("./data-input/sizes.dat", "r");
    int len = -1, temp;
    while (!feof(fp)) { fscanf(fp, "%d", &temp); len++; }
    rewind(fp);
    int sizes[len];
    for (int i = 0; i < len; i++)
        fscanf(fp, "%d", &sizes[i]);
    fclose(fp);

    long int timetotal, timeiter;

    const char filepathtemp[] = "./data-input/size-00.dat";
    FILE *fi, *fo;

    // check for directory existence
    struct stat stats;
    stat("data-output", &stats);
    if (!S_ISDIR(stats.st_mode))
        system("mkdir data-output");
    stat("plots", &stats);
    if (!S_ISDIR(stats.st_mode))
        system("mkdir plots");


    // ================= SELECTION SORT =================
    timetotal = 0;
    fo = fopen("./data-output/q1a-data-sort-selection.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[24];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[18] = '0' + (i + 1) / 10;
        filepathcurr[19] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_selection_sort_time(sizes[i], fi);
        fclose(fi);

        fprintf(fo, "%d,%ld\n", sizes[i], timeiter);
        timetotal += timeiter;
    }

    printf("selection sort completed in %.2lfs\n", ((double) timetotal / 1e3));
    fclose(fo);


    // ================= INSERTION SORT =================
    timetotal = 0;
    fo = fopen("./data-output/q1b-data-sort-insertion.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[24];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[18] = '0' + (i + 1) / 10;
        filepathcurr[19] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_insertion_sort_time(sizes[i], fi);
        fclose(fi);

        fprintf(fo, "%d,%ld\n", sizes[i], timeiter);
        timetotal += timeiter;
    }

    printf("insertion sort completed in %.2lfs\n", ((double) timetotal / 1e3));
    fclose(fo);


    // ================== BUBBLE SORT ==================
    timetotal = 0;
    fo = fopen("./data-output/q1c-data-sort-bubble.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[24];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[18] = '0' + (i + 1) / 10;
        filepathcurr[19] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_bubble_sort_time(sizes[i], fi);
        fclose(fi);

        fprintf(fo, "%d,%ld\n", sizes[i], timeiter);
        timetotal += timeiter;
    }

    printf("bubble sort completed in %.2lfs\n", ((double) timetotal / 1e3));
    fclose(fo);


    // calling BASH script for plotting
    system("chmod u+x q1-plot.sh");
    system("./q1-plot.sh");


    return 0;
}
