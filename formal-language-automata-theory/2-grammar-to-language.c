// Inputs Grammar: Language Production Rules
// Outputs Language to a certain level and general form
// Entry format:
//     S>zBy/z
//     B>a/#  where
//  UPPERCASE means non-terminal
//  LOWERCASE means terminal
//  # means null

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define clear() system("cls")               //windows
//#define clear() printf("\033[H\033[J")    //linux

typedef struct language{
    char *lan;
    int level;
    struct language **ch;
}   node;

typedef struct prodRule{
    char v;
    char **ar;
}   rule;

void generateTree(node *, rule **, int, int, int);
void traverseTree(node *, int, int);
rule *makeRule(char *);
void printStr(char *);
int lenStr(char *);

int main(int argc, char const *argv[]){
    clear();
    printf("Enter number of lines: ");
    int n; scanf("%d", &n); rule *a[n];
    printf("Enter Production Rule:\n");
    for(int i = 0; i < n; i++){
        char *s = (char *) malloc(sizeof(char) * 128);
        printf("  "); scanf("%s", s);
        a[i] = makeRule(s);
    }
    printf("Enter number of levels: ");
    int z; scanf("%d", &z); printf("\n");

    node *root = (node *) malloc(sizeof(node));
    root -> lan = (char *) malloc(sizeof(char) * 2);
    root -> lan[0] = a[0] -> v; root -> lan[1] = '\0';
    generateTree(root, a, n, z, 0);
    printf("  Tree\n  ----\n");
    traverseTree(root, z, 0);
    printf("\n");

    return 0;
}

rule *makeRule(char *str){
    char s[strlen(str) + 1]; s[strlen(str)] = '/';
    for(int i = 0; str[i] != '\0'; i++) s[i] = str[i];

    rule *temp = (rule *) malloc(sizeof(rule));
    temp -> v = s[0];
    int n = 0, p = 0, q = 0, r = 2;
    for(int i = 2; s[i] != '\0'; i++)
        if(s[i] == '/') n++;
    temp -> ar = (char **) malloc(sizeof(char *) * n);
    for(int i = 2; s[i] != '\0'; i++){
        if(s[i] == '/'){
            char *srl = (char *) malloc(sizeof(char) * (i - r + 1));
            srl[i - r] = '\0';
            for(int j = 0; j < (i - r); j++)
                srl[q++] = s[r + j];
            temp -> ar[p] = srl;
            p++; q = 0; r = i + 1;
        }
    }
    return temp;
}

void generateTree(node *r, rule **a, int rn, int n, int z){
    if(z == n)  return;
    r -> level = z;
    int nt = 0, tn = 0;
    for(int i = 0; (r -> lan[i]) != '\0'; i++){
        int temp = (int) (r -> lan[i]);
        if(temp >= 65 && temp <= 90)   nt++;
        if(temp >= 97 && temp <= 122)  tn++;
    }
    if(nt == 0) return;
    char nta[nt], tna[tn]; int p = 0, q = 0;
    for(int i = 0; (r -> lan[i]) != '\0'; i++){
        int temp = r -> lan[i];
        if(temp >= 65 && temp <= 90)    nta[p++] = (char) temp;
        if(temp >= 97 && temp <= 122)   tna[q++] = (char) temp;
    }

    int nch = 1;
    for(int i = 0; i < nt; i++){
        char x = nta[i]; int index;
        for(int j = 0; j < rn; j++){
            if(a[j] -> v == x){     index = j; break;   }
        }
        int chd = 0;
        for(int j = 0; a[i] -> ar[j] != '\0'; j++)  chd++;
        nch *= chd;
    }

    char *children[nch]; int chindex = 0;
    for(int i = 0; i < nt; i++){
        char x = nta[i]; int index;
        for(int j = 0; j < rn; j++){
            if(a[j] -> v == x){     index = j; break;   }
        }
        int chd = 0;
        for(int j = 0; a[i] -> ar[j] != '\0'; j++)  chd++;
        char **ar = (char **) malloc(sizeof(char *) * (chd + 1));
        ar[chd] = NULL;
        for(int j = 0; a[i] -> ar[j] != '\0'; j++)  ar[j] = a[index] -> ar[j];
        for(int j = 0; j < chd; j++){
            char temp[128]; int tc = 0;
            for(int k = 0; (r -> lan[k]) != '\0'; k++){
                char xf = r -> lan[k];
                if(xf == x){
                    for(int l = 0; a[index] -> ar[j][l] != '\0'; l++)
                        temp[tc++] = a[index] -> ar[j][l];
                }
                else    temp[tc++] = xf;
            }   temp[tc] = '\0';
            int len = 0;
            for(int k = 0; temp[k] != '\0'; k++)    len++;
            children[chindex] = (char *) malloc(sizeof(char) * (len + 1));
            for(int k = 0; k < len; k++)    children[chindex][k] = temp[k];
            children[chindex][len] = '\0'; chindex++;
        };
    }

    r -> ch = (node **) malloc(sizeof(node *) * nch);
    //printf("|"); printStr(r -> lan); printf("|\n");
    for(int i = 0; i < nch; i++){
        //printf("-- "); printStr(children[i]); printf("\n");
        node *child = (node *) malloc(sizeof(node));
        int len = lenStr(children[i]);
        child -> lan = (char *) malloc(sizeof(char) * (len + 1));
        for(int j = 0; j < len; j++)
            child -> lan[j] = children[i][j];
        child -> lan[len] = '\0';
        r -> ch[i] = child;
        generateTree(child, a, rn, n, z + 1);
    }
}

void traverseTree(node *r, int n, int z){
    if(z == n)  return;
    printf("  "); for(int i = 0; i < r -> level; i++)  printf("    ");
    printStr(r -> lan); printf("\n");
    int nch; for(nch = 0; r -> ch[nch] != '\0'; nch++);
    for(int i = 0; i < nch; i++)    traverseTree(r -> ch[i], n, z + 1);
    //printf("ZZZ\n");
}

void printStr(char *a){
    if(lenStr(a) == 2 && a[0] == '#' && !isalpha(a[1])){
        printf("#"); return;
    }
    for(int k = 0; a[k] != '\0'; k++){
        if(a[k] == '#') continue;
        printf("%c", a[k]);
    }
}

int lenStr(char *a){
    int k; for(k = 0; a[k] != '\0'; k++);
    return k;
}