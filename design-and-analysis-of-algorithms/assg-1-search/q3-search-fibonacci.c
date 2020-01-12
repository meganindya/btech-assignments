#include <stdio.h>
#include <stdlib.h>


// returns number of iterations of algorithm loop
int getSearchFibonacciTime(int n) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
        for (long int i = 0; i < n; i++)
            arr[i] = i;

    //============================
    int key = -1, iterations = 0;
    
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

        iterations++;
    }

    if (fibM1 == 1 && arr[offset + 1] == key)
        goto exit;
    //============================

    exit:
    return iterations;
}

// driver
int main(int argc, char *argv) {
    FILE *fp = fopen("q3-data.csv", "w");
    long int n = 10000;
    
    do {
        fprintf(fp, "%ld,%d\n", n, getSearchFibonacciTime(n));
    } while((n <<= 1) < 1000000000);
    
    fclose(fp);
    system("./q3-plot.sh"); // calls Bash script for plotting
    
    return 0;
}
