// creates random data lists of different sizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {
    int sizes[] = { 1000, 5000, 10000, 50000, 100000 };
    int len = sizeof(sizes) / sizeof(int);
    
    const char filepathtemp[] = "./data-input/size-00.csv";

    for (int i = 0; i < len; i++) {
        char filepathcurr[24];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[18] = '0' + (i + 1) / 10;
        filepathcurr[19] = '0' + (i + 1) % 10;
        FILE *fp = fopen(filepathcurr, "w");

        srand(time(0));
        for (int j = 0; j < sizes[i]; j++)
            fprintf(fp, "%d\n", 1 + (int) (rand() % 33200));
        
        fclose(fp);
    }

    return 0;
}
