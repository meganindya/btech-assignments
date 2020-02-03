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


// =================== MERGE SORT ===================
// utility function for merging
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k] = L[i++];
        else
            arr[k] = R[j++];
        k++;
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// returns minimum of two integers
int min(int a, int b) {
    return (a > b) ? b : a;
}

// returns time taken to run algorithm
long int get_merge_sort_time(int n, FILE *fp) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    for (int curr_size = 1; curr_size <= n-1; curr_size <<= 1) {
       for (int left_start = 0; left_start < n - 1; left_start += curr_size << 1) {
           int mid = min(left_start + curr_size - 1, n - 1);
           int right_end = min(left_start + 2 * curr_size - 1, n - 1);
           
           merge(arr, left_start, mid, right_end);
       }
    }
    //============================
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);

    // calculating total time taken by the program.
    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken += (end.tv_nsec - start.tv_nsec);
    return time_taken;
}

// =================== HEAP SORT ===================
// utility function for heapifying
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;

        heapify(arr, n, largest);
    }
}

// returns time taken to run algorithm
long int get_heap_sort_time(int n, FILE *fp) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    
    for (int i=n-1; i>=0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
    
        heapify(arr, i, 0);
    }
    //============================
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

    // fetch list of sizes
    FILE *fp = fopen("../data-input/sizes.dat", "r");
    int len = -1, temp;
    while (!feof(fp)) { fscanf(fp, "%d", &temp); len++; }
    rewind(fp);
    int sizes[len];
    for (int i = 0; i < len; i++)
        fscanf(fp, "%d", &sizes[i]);
    fclose(fp);

    long int timetotal, timeiter;

    const char filepathtemp[] = "../data-input/size-00.dat";
    FILE *fi, *fo;

    // check for directory existence
    struct stat stat1, stat2;
    stat("q2-data-output", &stat1);
    if (!S_ISDIR(stat1.st_mode))
        system("mkdir q2-data-output");
    stat("q2-plots", &stat2);
    if (!S_ISDIR(stat2.st_mode))
        system("mkdir q2-plots");
    
    FILE *fx = fopen("./q2-data-output/q2-time.txt", "w+");


    // =================== MERGE SORT ===================
    timetotal = 0;
    fo = fopen("./q2-data-output/q2a-data-sort-merge.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[25];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[19] = '0' + (i + 1) / 10;
        filepathcurr[20] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_merge_sort_time(sizes[i], fi);
        fclose(fi);

        fprintf(fo, "%d,%.2lf\n", sizes[i], ((double) timeiter / 1e6));
        timetotal += timeiter;
    }

    printf("merge sort completed in %.2lfms\n", ((double) timetotal / 1e6));
    fprintf(fx, "merge sort completed in %.2lfms\n", ((double) timetotal / 1e6));
    fclose(fo);


    // =================== HEAP SORT ===================
    timetotal = 0;
    fo = fopen("./q2-data-output/q2b-data-sort-heap.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[25];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[19] = '0' + (i + 1) / 10;
        filepathcurr[20] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_heap_sort_time(sizes[i], fi);
        fclose(fi);

        fprintf(fo, "%d,%.2lf\n", sizes[i], ((double) timeiter / 1e6));
        timetotal += timeiter;
    }

    printf("heap sort completed in %.2lfms\n", ((double) timetotal / 1e6));
    fprintf(fx, "heap sort completed in %.2lfms\n", ((double) timetotal / 1e6));
    fclose(fo);


    fclose(fx);

    return 0;
}
