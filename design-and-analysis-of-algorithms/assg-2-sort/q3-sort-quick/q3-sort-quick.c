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


// =================== QUICK SORT ===================
// utility function for partition
int partition(int arr[], int low, int high, int type) {
    int i = low - 1, pivotindex;
    if (type == 0)
        pivotindex = high;
    else
        pivotindex = low + 1 + rand() % (high - low);
    int pivot = arr[pivotindex];
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[pivotindex];
    arr[pivotindex] = temp;

    return i + 1;
}

// utility function for recursive calls
void sort(int arr[], int low, int high, int type) {
    if (low < high) {
        int pi = partition(arr, low, high, type);
        
        sort(arr, low, pi - 1, type);
        sort(arr, pi + 1, high, type);
    }
}

// *****
/*void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, int type) {
    int x = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
        if (arr[j] <= x)
            swap(&arr[++i], &arr[j]);

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int type) {
    int stack[high - low + 1], top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low  = stack[top--];

        int p = partition(arr, low, high);

        if (p - 1 > low) {
            stack[++top] = low;
            stack[++top] = p - 1;
        }

        if (p + 1 < high) {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }
}*/
// *****

// returns time taken to run algorithm
long int get_quick_sort_time(int n, FILE *fp, int type) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        fscanf(fp, "%d", &arr[i]);
    
    struct timespec start, end;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    //============================
    sort(arr, 0, n - 1, type);
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
    stat("q3-data-output", &stat1);
    if (!S_ISDIR(stat1.st_mode))
        system("mkdir q3-data-output");
    stat("q3-plots", &stat2);
    if (!S_ISDIR(stat2.st_mode))
        system("mkdir q3-plots");
    
    FILE *fx = fopen("./q3-data-output/q3-time.txt", "w+");


    // ================= QUICK SORT (ORG) =================
    timetotal = 0;
    fo = fopen("./q3-data-output/q3a-data-sort-quick-org.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[25];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[19] = '0' + (i + 1) / 10;
        filepathcurr[20] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_quick_sort_time(sizes[i], fi, 0);
        fclose(fi);

        fprintf(fo, "%d,%.2lf\n", sizes[i], ((double) timeiter / 1e6));
        timetotal += timeiter;
    }

    printf("quick sort (original) completed in %.2lfms\n", ((double) timetotal / 1e6));
    fprintf(fx, "quick sort (original) completed in %.2lfms\n", ((double) timetotal / 1e6));
    fclose(fo);


    // ================= QUICK SORT (MOD) =================
    timetotal = 0;
    fo = fopen("./q3-data-output/q3b-data-sort-quick-mod.csv", "w+");
    
    for (int i = 0; i < len; i++) {
        char filepathcurr[25];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[19] = '0' + (i + 1) / 10;
        filepathcurr[20] = '0' + (i + 1) % 10;
        
        fi = fopen(filepathcurr, "r");
        timeiter = get_quick_sort_time(sizes[i], fi, 1);
        fclose(fi);

        fprintf(fo, "%d,%.2lf\n", sizes[i], ((double) timeiter / 1e6));
        timetotal += timeiter;
    }

    printf("quick sort (modified) completed in %.2lfms\n", ((double) timetotal / 1e6));
    fprintf(fx, "quick sort (modified) completed in %.2lfms\n", ((double) timetotal / 1e6));
    fclose(fo);


    fclose(fx);

    return 0;
}
