#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// linked list nodes for production rules
typedef struct list {
    char val;
    int type;
    struct list *next;
} node;

typedef struct NTnode {
    char val;
    int c_der;
    node **derivatives;
} NTnode;


// function declarations
void storeNonTerminals();
void storeTerminals();
void storeProductionRules();
void storeStartSymbol();

void printGrammar();
void groupRules();

void findFirst(char, char *, int *);
int derivesEpsilon(char);
void removeDuplicates(char *, int *);


// globals
int c_nt, c_tm, c_pr;
char *nt, *tm, ss;
node **pr;
int symbols[256][2];
NTnode **prs;


// main
int main(int argc, char *argv[]) {
    system("clear");

    storeNonTerminals();
    storeTerminals();
    storeProductionRules();
    storeStartSymbol();

    printGrammar();

    groupRules();

    printf("\n");
    for (int i = 0; i < c_nt; i++) {
        printf("FIRST(%c) : { ", nt[i]);
        char temp[64]; int len = 0;
        findFirst(nt[i], temp, &len);
        removeDuplicates(temp, &len);
        printf("%c", temp[0]);
        for (int j = 1; j < len; j++)
            printf(", %c", temp[j]);
        printf(" }\n");
    }

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
        if (strlen(temp) < 3) {
            printf("Invalid Rule! Retry");
            i--; continue;
        }

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
        pr[i] = head;
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


void printGrammar() {
    printf("\nGrammar:\n--------");
    printf("\nNon-terminals: %c", nt[0]);
    for (int i = 1; i < c_nt; i++)
        printf(", %c", nt[i]);
    printf("\n");

    printf("\nTerminals: %c", tm[0]);
    for (int i = 1; i < c_tm; i++)
        printf(", %c", tm[i]);
    printf("\n");

    printf("\nProduction Rules:\n");
    for (int i = 0; i < c_pr; i++) {
        node *curr = pr[i];
        printf("  ");
        while (curr != NULL) {
            printf("%c", curr -> val);
            curr = curr -> next;
        }
        printf("\n");
    }

    printf("\nStart Symbol: %c\n", ss);
}


void groupRules() {
    prs = (NTnode **) malloc(sizeof(NTnode *) * c_nt);
    for (int i = 0; i < c_nt; i++) {
        NTnode *temp = (NTnode *) malloc(sizeof(NTnode));
        temp -> val = nt[i];

        int count = 0;
        for (int j = 0; j < c_pr; j++) {
            if ((pr[j] -> val) == nt[i])
                count++;
        }

        temp -> c_der = count;
        temp -> derivatives = (node **) malloc(sizeof(node *) * count);

        int k = 0;
        for (int j = 0; j < c_pr; j++) {
            if ((pr[j] -> val) == nt[i])
                temp -> derivatives[k++] = ((pr[j] -> next) -> next);
        }

        prs[i] = temp;
    }

    printf("\nProduction Rules:\n");
    for (int i = 0; i < c_nt; i++) {
        printf("  %c -> ", (prs[i] -> val));
        for (int j = 0; j < (prs[i] -> c_der); j++) {
            if (j != 0) printf(" | ");
            node *curr = prs[i] -> derivatives[j];
            while (curr != NULL) {
                printf("%c", curr -> val);
                curr = curr -> next;
            }
        }
        printf("\n");
    }
}


void findFirst(char NT, char *first, int *k) {
    int index;
    for (int i = 0; i < c_nt; i++) {
        if (nt[i] == NT) {
            index = i;
            break;
        }
    }

    for (int i = 0; i < (prs[index] -> c_der); i++) {
        node *curr = prs[index] -> derivatives[i];
        if (symbols[curr -> val][0] == 2)
            first[(*k)++] = curr -> val;
        else {
            while (curr != NULL && derivesEpsilon(curr -> val)) {
                findFirst(curr -> val, first, k);
                curr = curr -> next;
            }
            if (curr != NULL)
                findFirst(curr -> val, first, k);
        }
    }

    first[*k] = '\0';
}

int derivesEpsilon(char NT) {
    int index;
    for (int i = 0; i < c_nt; i++) {
        if (nt[i] == NT) {
            index = i;
            break;
        }
    }

    int flag = 0;
    for (int i = 0; i < (prs[index] -> c_der); i++) {
        if ((prs[index] -> derivatives[i]) -> val == '.') {
            flag = 1;
            break;
        }
    }

    return flag;
}

void removeDuplicates(char *temp, int *len) {
    for (int i = 0; i < (*len); i++) {
        for (int j = i + 1; j < (*len); j++) {
            if (temp[j] == temp[i])
                temp[j] = 10;
        }
    }

    int j = 0;
    for (int i = 0; i < (*len); i++) {
        while (temp[j] == 10)   j++;
        temp[i] = temp[j++];
    }

    for (j = 0; temp[j] != '\0'; j++);
    *len = j;
}
