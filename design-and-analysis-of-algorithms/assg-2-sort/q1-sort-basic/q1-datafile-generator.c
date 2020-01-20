#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    const char *filepaths[5] = {
        "./data-input/size-1.csv",
        "./data-input/size-2.csv",
        "./data-input/size-3.csv",
        "./data-input/size-4.csv",
        "./data-input/size-5.csv"
    };

    int sizes[] = { 1000, 5000, 10000, 50000, 100000 };
    for (int i = 0; i < 5; i++) {
        FILE *fp = fopen(filepaths[i], "w");

        srand(time(0));
        for (int j = 0; j < sizes[i]; j++)
            fprintf(fp, "%d\n", 1 + (int) (rand() % 33200));
        
        fclose(fp);
    }

    return 0;
}
