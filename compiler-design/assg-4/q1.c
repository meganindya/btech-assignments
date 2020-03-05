#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
    system("clear");
    int c_nt, c_tm, c_pr;

    printf("Enter number of Non-terminals: ");
    scanf("%d", &c_nt);

    char nt[c_nt];
    for (int i = 0; i < c_nt; i++) {
        printf("NT %d: ", (i + 1));
        scanf(" %c", &nt[i]);
    }

    printf("\nEnter number of Terminals: ");
    scanf("%d", &c_tm);

    char tm[c_tm];
    for (int i = 0; i < c_tm; i++) {
        printf("TM %d: ", (i + 1));
        scanf(" %c", &tm[i]);
    }

    printf("\nEnter number of Production Rules: ");
    scanf("%d", &c_pr);

    char pr[c_pr][64];
    for (int i = 0; i < c_pr; i++) {
        printf("RULE %d: ", (i + 1));
        scanf("%s", pr[i]);
    }

    /*char ss;
    do {
        printf("\nEnter Start Symbol: ");
        scanf("%c", &ss);

        int flag = 0;
        for (int i = 0; i < (sizeof(nt) / sizeof(int)); i++)
            if (ss == nt[i]) {
                flag = 1;
                break;
            }

        if (flag == 0)
            printf("Invalid! Retry\n");
    } while(1);*/


    for (int i = 0; i < c_nt; i++)
        printf("%c\n", nt[i]);
    printf("\n");

    for (int i = 0; i < c_tm; i++)
        printf("%c\n", tm[i]);
    printf("\n");

    for (int i = 0; i < (sizeof(nt) / sizeof(int)); i++)
        printf("%s\n", pr[i]);
    printf("\n");

    //printf("%c\n", ss);

    return 0;
}
