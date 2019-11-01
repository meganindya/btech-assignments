#include <stdlib.h>
#include <stdio.h>
#include "fcyc2.h"          // K-best measurement timing routines
#include "clock.h"          // routines to access the cycle counter

#define MINBYTES (1 << 10)              // Working set size ranges from 1 KB
#define MAXBYTES (1 << 26)              // ... up to 64 MB
#define MAXSTRIDE 32                    // Strides range from 1 to 32
#define STRIDESTRIDE 2                  // increment stride by this amount each time
#define MAXELEMS MAXBYTES/sizeof(int)


int data[MAXELEMS];         // The array to be traversed


void    init_data(int *, int);
void    test(int, int);
double  run(int, int, double);




int main() {
    int size;        // Working set size (in bytes)
    int stride;      // Stride (in array elements)
    double Mhz;      // Clock frequency

    FILE *fp = fopen("results.dat", "w");

    init_data(data, MAXELEMS); // Initialize each element in data to 1
    Mhz = mhz(0);              // Estimate the clock frequency

    printf("Clock frequency is approx. %.1f MHz\n", Mhz);
    printf("Memory mountain (MB/sec)\n");
    
    fprintf(fp, "17\t");
    printf("\t");
    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
        fprintf(fp, "%d\t", stride);
	    printf("s%d\t", stride);
    }
    fprintf(fp, "\n");
    printf("\n");


    for (size = MAXBYTES; size >= MINBYTES; size >>= 1) {
	    if (size > (1 << 20))
	        printf("%dm\t", size / (1 << 20));
	    else
	        printf("%dk\t", size / 1024);


        fprintf(fp, "%d\t", size);
	    for (stride = 1; stride <= MAXSTRIDE; stride += STRIDESTRIDE) {
	        double temp = run(size, stride, Mhz);
            fprintf(fp, "%.0f\t", temp);
	        printf("%.0f\t", temp);
	    }
        fprintf(fp, "\n");
	    printf("\n");
    }
    fclose(fp);

    system("gnuplot -p 'plot.gnuplot'");

    exit(0);
}


// initializes the array
void init_data(int *data, int n) {
    int i;

    for (i = 0; i < n; i++)
	    data[i] = 1;
}


// test function
void test(int elems, int stride) {
    int i, result = 0; 
    volatile int sink; 

    for (i = 0; i < elems; i += stride)
	    result += data[i];
    
    sink = result;  // to prevent compiler from optimizing away the loop
}


// run test(elems, stride) and return read throughput (MB/s)
double run(int size, int stride, double Mhz) {
    double cycles;
    int elems = size / sizeof(int);

    test(elems, stride);                     // warm up the cache
    cycles = fcyc2(test, elems, stride, 0);  // call test(elems,stride)
    return (size / stride) / (cycles / Mhz); // convert cycles to MB/s
}