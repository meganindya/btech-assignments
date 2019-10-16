// Produces state table for detecting a sequence
// in a long sequence where every state is a
// respective number of match found upto that
// number of bits

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define clear() system("cls")               //windows
//#define clear() printf("\033[H\033[J")    //linux

void stateTable(char *, char *);
int findNext(char *, int, int);
int findMatch(int *, int *, int, int);

int main(int argc, char const *argv[]){
    clear();
    printf("Enter Long Sequence\t: ");
    char s[128]; scanf("%s", s);
    printf("Enter Search Sequence\t: ");
    char x[128]; scanf("%s", x);
    stateTable(x, s);

    return 0;
}

void stateTable(char *x, char *s){
    int n = strlen(x), a[n][4];
    for(int i = 0; i < n; i++){
        int z1 = (int)(x[i] - '0');
        int z2 = abs(z1 - 1);

        a[i][(2 * z1)] = i + 1;     //Original NS
        a[i][(2 * z1) + 1] = 0;     //Original OP
        a[i][(2 * z2) + 1] = 0;     //Complement OP

        if(i == (n - 1)){           //for state n
            a[i][(2 * z1)] = findNext(x, z1, n - 1);    //Original NS
            a[i][(2 * z1) + 1] = 1;                     //Original OP
        }

        if(i == 0)  a[i][(2 * z2)] = 0;         //Complement NS for state 1
        else        a[i][(2 * z2)] = findNext(x, z2, i);    //Complement NS
    }

    printf("\n  State Table:\n  ------------\n");
    printf("  PS\t|\t\t  NS/OP\n");
    printf("-----------------------------------------\n");
    printf("\t|\t    0\t\t    1\n");
    printf("-----------------------------------------\n");
    for(int i = 0; i < n; i++){
        printf("  S%d\t|\t", (i + 1));
        for(int j = 0; j < 4; j++){
            if(j % 2 == 0)  printf("S%d\t", (a[i][j] + 1));
            else            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Sequence\t: ");
    for(int i = 0; s[i] != '\0'; i++)   printf("%c ", s[i]);    printf("\n");
    printf("Matched\t\t: ");
    int state = 0;
    for(int i = 0; s[i] != '\0'; i++){
        int w = (int)(s[i] - '0');
        printf("%d ", a[state][(2 * w) + 1]);
        state = a[state][(2 * w)];
    }
    printf("\n\n");
}

int findNext(char *x, int z, int k){
    for(int i = k; i > 0; i--){
        int temp1[i], temp2[i]; temp2[i - 1] = z;
        int g = 0, f = k - i + 1;
        for(int j = 0; j < i; j++)      temp1[j] = (int)(x[j] - '0');
        for(int j = 0; j < i - 1; j++)  temp2[g++] = (int)(x[f++] - '0');
        if(findMatch(temp1, temp2, i, 0))   return i;
    }
    return 0;
}

int findMatch(int *a, int *b, int n, int z){
    if(z == n)          return 1;
    if(a[z] != b[z])    return 0;
    findMatch(a, b, n, ++z);
}