#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// linked list node for production rules
typedef struct list {
    char val;
    int type;
    struct list *next;
} node;


// function declarations
void storeNonTerminals();
void storeTerminals();
void storeProductionRules();
void storeStartSymbol();


// globals
int c_nt, c_tm, c_pr;
char *nt, *tm, ss;
node **pr;

int symbols[256][2];


// main
int main(int argc, char *argv[]) {
    system("clear");

    storeNonTerminals();

    storeTerminals();

    storeProductionRules();

    storeStartSymbol();


    return 0;
}


// input functions
void storeNonTerminals() {
    printf("Enter number of Non-terminals: ");
    scanf("%d", &c_nt);

    nt = (char *) malloc(sizeof(char) * c_nt);
    for (int i = 0; i < c_nt; i++) {
        printf("NT %d: ", (i + 1));
        scanf(" %c", &nt[i]);
        symbols[nt[i]][0] = 1;
    }
}

void storeTerminals() {
    printf("\nEnter number of Terminals: ");
    scanf("%d", &c_tm);

    tm = (char *) malloc(sizeof(char) * c_tm);
    for (int i = 0; i < c_tm; i++) {
        printf("TM %d: ", (i + 1));
        char temp; scanf(" %c", &temp);

        int flag = 0;
        for (int i = 0; i < c_nt; i++) {
            if (temp == nt[i]) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {
            printf("\'%c\' already used as non-terminal. Retry\n", temp);
            i--;
        } else {
            tm[i] = temp;
            symbols[tm[i]][0] = 2;
        }
    }
}

void storeProductionRules() {
    do {
        printf("\nEnter number of Production Rules: ");
        scanf("%d", &c_pr);
        if (c_pr < c_nt)
            printf("Production Rules' count less than non-terminals' count\n");
        else
            break;
    } while(1);

    pr = (node **) malloc(sizeof(node *) * c_pr);
    for (int i = 0; i < c_pr; i++) {
        printf("RULE %d: ", (i + 1));
        char temp[64];
        scanf("%s", temp);

        if (symbols[temp[0]][0] != 1) {
            printf("First symbol has to be a non-terminal\n");
            i--; continue;
        } else
            symbols[temp[0]][1] = 1;

        if (temp[1] != '>') {
            printf("Invalid Rule! Retry\n");
            i--; continue;
        }

        pr[i] = NULL;
        node *head = pr[i], *curr = pr[i];
        for (int j = 0; temp[j] != '\0'; j++) {
            char x = temp[j];
            if (x != '>' && symbols[x][0] == 0) {
                printf("\'%c\' is invalid. Retry\n", x);
                // """"ISSUE""""
                // free nodes already allocated
                // """""""""""""
                i--; break;
            } else {
                node *new = (node *) malloc(sizeof(node));
                new -> val = x;
                new -> type = symbols[x][0];
                if (x == '>')
                    new -> type = -1;
                new -> next = NULL;

                if (head == NULL)
                    head = curr = new;
                else {
                    curr -> next = new;
                    curr = new;
                }
            }
        }
    }

    int flag = 0;
    for (int i = 0; i < c_nt; i++) {
        if (symbols[nt[i]][1] == 0) {
            printf("Missing Production Rule/s. Retry\n");
            flag = 1; break;
        }
    }
    // """"ISSUE""""
    // free nodes already allocated
    // """""""""""""
    if (flag == 1)
        storeProductionRules();
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
            printf("Start Symbol has to be a non-terminal. Retry\n");
        else
            break;
    } while(1);
}
