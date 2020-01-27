// creates random data lists of different sizes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {
    FILE *fp = fopen("./data-input/sizes.dat", "r");
    int len = -1, temp;
    while (!feof(fp)) { fscanf(fp, "%d", &temp); len++; }
    rewind(fp);
    int sizes[len];
    for (int i = 0; i < len; i++)
        fscanf(fp, "%d", &sizes[i]);
    fclose(fp);
    
    const char filepathtemp[] = "./data-input/size-00.dat";

    for (int i = 0; i < len; i++) {
        char filepathcurr[24];
        strcpy(filepathcurr, filepathtemp);
        filepathcurr[18] = '0' + (i + 1) / 10;
        filepathcurr[19] = '0' + (i + 1) % 10;
        fp = fopen(filepathcurr, "w");

        srand(time(0));
        for (int j = 0; j < sizes[i]; j++)
            fprintf(fp, "%d\n", 1 + (int) (rand() % 33200));
        
        fclose(fp);
    }

    return 0;
}
