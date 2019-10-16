#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct bucket{
    int data;
    struct bucket *next;
}   node;

int* input(int *);
int* sort(int *, int, int, int);
void insert(node **, int, int);

int main(void){
    int n, *inp = input(&n), *out, max = INT_MIN, maxl = 0;
    //int inp[5] = {122, 759, 317, 672, 531}; n = 5;
    for(int i = 0; i < n; i++)
        if(inp[i] > max)    max = inp[i];
    while(max != 0){    max /= 10; maxl++;  }
    printf("\tSorted Sequence :\t");
    out = sort(inp, n, maxl, 0);
    for(int i = 0; i < n; i++)  printf("%d ", out[i]);
    printf("\n\n\n");
    return 0;
}

int* sort(int *inp, int n, int l, int z){
    if(z == l)  return inp;
    node *bck[10] = {NULL};
    for(int i = 0; i < n; i++){
        int temp = inp[i];
        for(int i = 0; i < z; i++)  temp /= 10;
        insert(bck, temp % 10, inp[i]);
    }
    int *out = (int *) malloc(sizeof(int) * n), k = 0;
    for(int i = 0; i < 10; i++){
        if(bck[i] == NULL)  continue;
        node *current = bck[i];
        while(current != NULL){
            out[k++] = current -> data;
            current = current -> next;
        }
    }
    sort(out, n, l, z + 1);
}

void insert(node **a, int x, int v){
    node *temp = (node *) malloc(sizeof(node));
    temp -> data = v; temp -> next = NULL;
    if(a[x] == NULL){  a[x] = temp; return ;  }
    node *current = a[x];
    while(current -> next != NULL)  current = current -> next;
    current -> next = temp;
}

int* input(int *n){
    char s[128]; int a[64], k = 0;
    for(int i = 0; i < 64; i++) a[i] = 0;
    printf("\n\n\tEnter Sequence :\t");
    scanf("%[^\n]s", s); s[strlen(s)] = ' ';
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == ' '){    k++; continue;  }
        a[k] = (a[k] * 10) + s[i] - (int)'0';
    }   *n = k;
    int *out = (int *) malloc(sizeof(int) * k);
    for(int i = 0; i < k; i++)  out[i] = a[i];
    return out;
}
