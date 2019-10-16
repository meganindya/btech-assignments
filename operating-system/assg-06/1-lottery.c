#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    printf("\n");
    int n = 10;
    if(argc > 1)    n = atoi(argv[1]);
    printf("Tickets : %d\n\n", n);

    int pcount = 10;
    int pcb[pcount][4];

    srand(time(0));
    int tf = n - (pcount - 1), ts = 0;
    for(int i = 0; i < pcount - 1; i++) {
        pcb[i][0] = i + 1;
        pcb[i][1] = (rand() % tf) + 1;
        pcb[i][1] = (rand() % pcb[i][1]) + 1;

        ts += pcb[i][1];
        tf = n - (pcount - i - 2) - ts;
    }
    pcb[pcount - 1][0] = pcount;
    pcb[pcount - 1][1] = tf;


    pcb[0][2] = 1; pcb[0][3] = pcb[0][1];
    for(int i = 1; i < pcount; i++) {
        pcb[i][2] = pcb[i - 1][3] + 1;
        pcb[i][3] = pcb[i][1] + pcb[i][2] - 1;
    }

    printf("\t\tT\tS\tE\n\n");
    for(int i = 0; i < pcount; i++)
        printf("Process %d\t%d\t%d\t%d\n",
            pcb[i][0], pcb[i][1], pcb[i][2], pcb[i][3]);
    printf("\n");

    int prs[n / 2], prc[pcount];
    for(int i = 0; i < pcount; i++)  prc[i] = 0;
    for(int i = 0; i < n / 2;  i++)  prs[i] = 0;

    printf("After %d iterations:\n\n", (n / 4));
    for(int i = 0; i < n / 4; i++) {
        int t = (rand() % n) + 1;
        //printf("%d\t|| %d\n", (i + 1), t);
        for(int j = 0; j < pcount; j++) {
            if(pcb[j][2] <= t && t <= pcb[j][3]) {
                //printf("\t%d - %d %d %d\n", (j + 1), pcb[j][2], t, pcb[j][3]);
                prs[i] = j + 1;
                prc[j]++;
                break;
            }
        }
    }

    /*for(int i = 0; i < n / 4; i++) {
        printf("%d\t%d\n", (i + 1), prs[i]);
    }   printf("\n");*/

    for(int i = 0; i < pcount; i++) {
        printf("Process %d\t%d\n", (i + 1), prc[i]);
    }   printf("\n");



    printf("After %d iterations:\n\n", (n / 2));
    for(int i = n / 4; i < n / 2; i++) {
        int t = (rand() % n) + 1;
        //printf("%d\t|| %d\n", (i + 1), t);
        for(int j = 0; j < pcount; j++) {
            if(pcb[j][2] <= t && pcb[j][3] >= t) {
                //printf("\t%d - %d %d %d\n", (j + 1), pcb[j][2], t, pcb[j][3]);
                prs[i] = j + 1;
                prc[j]++;
                break;
            }
        }
    }

    /*for(int i = 0; i < n / 2; i++) {
        printf("%d\t%d\n", (i + 1), prs[i]);
    }   printf("\n");*/

    for(int i = 0; i < pcount; i++) {
        printf("Process %d\t%d\n", (i + 1), prc[i]);
    }

    printf("\n");
    return 0;
}