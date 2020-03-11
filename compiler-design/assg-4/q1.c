#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// function declarations
void storeNonTerminals();
void storeTerminals();
void storeProductionRules();
void storeStartSymbol();


// globals
int c_nt, c_tm, c_pr;
char *nt, *tm, **pr, ss;


int main(int argc, char *argv[]) {
    system("clear");

    storeNonTerminals();

    storeTerminals();

    storeProductionRules();

    storeStartSymbol();


    return 0;
}


void storeNonTerminals() {
    printf("Enter number of Non-terminals: ");
    scanf("%d", &c_nt);

    nt = (char *) malloc(sizeof(char) * c_nt);
    for (int i = 0; i < c_nt; i++) {
        printf("NT %d: ", (i + 1));
        scanf(" %c", &nt[i]);
    }
}

void storeTerminals() {
    printf("\nEnter number of Terminals: ");
    scanf("%d", &c_tm);

    tm = (char *) malloc(sizeof(char) * c_tm);
    for (int i = 0; i < c_tm; i++) {
        printf("TM %d: ", (i + 1));
        scanf(" %c", &tm[i]);
    }
}

void storeProductionRules() {
    printf("\nEnter number of Production Rules: ");
    scanf("%d", &c_pr);

    pr = (char **) malloc(sizeof(char *) * c_pr);
    for (int i = 0; i < c_pr; i++) {
        pr[i] = (char *) malloc(sizeof(char) * 64);
        printf("RULE %d: ", (i + 1));
        char temp[64];
        scanf("%s", temp);
        strcpy(pr[i], temp);
        puts(pr[i]);
    }
}

void storeStartSymbol() {
    do {
        printf("\nEnter Start Symbol: ");
        scanf(" %c", &ss);

        int flag = 0;
        for (int i = 0; i < c_nt; i++) {
            if (ss == nt[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
            printf("Invalid! Retry\n");
        else
            break;
    } while(1);
}
