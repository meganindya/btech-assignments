#include <stdio.h>
#include <stdlib.h>


// returns number of iterations of algorithm loop
int getSearchBinaryTime(int n) {
    // array declared in heap, to avoid space restrictions
    int *arr = malloc(sizeof(int) * n);
    for (long int i = 0; i < n; i++)
        arr[i] = i;

    //============================
    int key = -1, iterations = 0;
    
    int low = 0, high = n - 1;

    while (high >= low) {
        long int mid = low + ((high - low) / 2);
        
        if (arr[mid] == key)
            break;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
        
        iterations++;
    }
    //============================

    return iterations;
}

// driver
int main(int argc, char *argv) {
    FILE *fp = fopen("q2-data.csv", "w");
    long int n = 10000;

    do {
        fprintf(fp, "%ld,%d\n", n, getSearchBinaryTime(n));
    } while((n <<= 1) < 1000000000);

    fclose(fp);
    system("./q2-plot.sh"); // calls Bash script for plotting

    return 0;
}
