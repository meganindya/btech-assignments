#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define clear() printf("\033[H\033[J")

typedef struct ht{
    int key;
    struct ht *next;
}   node;

void insert(node **, int);
void search(node **, int);
int hash(int);
void display(node **);

int main(void){
    int ch, val; node *a[SIZE] = {NULL};
    clear(); loop: display(a);
    printf("\n====\nPick");
    printf("\n 1 to INSERT");
    printf("\n 2 to SEARCH");
    printf("\n0 to EXIT");
    printf("\n\nEnter : ");
    scanf("%d", &ch);
    if(ch == 0) return 0;

    if(ch == 1 || ch == 2){
    	printf("\nEnter Value : ");
    	scanf("%d", &val);
    }
    if(ch == 1)         insert(a, val);
    else if(ch == 2)    search(a, val);
    else{   clear(); printf("INVALID entry! Retry\n");    }
    goto loop;
}

void display(node **a){
	printf("\nHash Table\n==========\n");
	for(int i = 0; i < SIZE; i++){
    	printf("%d   -   ", i);
    	node *t = a[i];
    	if(t == NULL){	printf("(nil)\n"); continue;	}
    	while(t != NULL){
    		printf("%d\t", t -> key);
    		t = t -> next;
    	}	printf("\n");
	}
}

void insert(node **a, int val){
	int x = hash(val);
    node *v = (node *) malloc(sizeof(node));
    v -> key = val; v -> next = NULL;
    if(a[x] == NULL){  a[x] = v; goto skip;   }
    node *t = a[x];
    while((t -> next) != NULL)  t = t -> next;
    t -> next = v;
    skip: clear(); printf("-- %d INSERTED\n", val);
}

void search(node **a, int val){
	clear(); int x = hash(val);
	node *t = a[x];
	while(t != NULL){
		if(t -> key == val){
			printf("-- Match FOUND for key %d\n", val); break;
		}	t = t -> next;
	}
	if(t == NULL){	printf("-- Match NOT FOUND\n"); return;	}
}

int hash(int x){
    return x % SIZE;
}
