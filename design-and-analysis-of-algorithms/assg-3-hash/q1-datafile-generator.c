#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    FILE *fp = fopen("./q1-data-input/keys.dat", "w+");

    srand(time(0));
    for (int i = 0; i < 100000; i++)
        fprintf(fp, "%d\n", 1 + (int) (rand() % 67107840));

    fclose(fp);
    return 0;
}
