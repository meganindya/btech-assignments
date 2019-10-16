#include <stdio.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

typedef struct tree{
    int lkey, ukey;
    struct tree *lc, *mc, *rc;
}   node;

void ins(node **, int);
void inorder(node *);

int main(void){
    node *root = NULL; int choice, val;
    clear(); loop:
	if(root != NULL)	printf("\nINORDER : ");
	inorder(root);
    printf("\n=====");
    printf("\n  1 to INSERT");
    printf("\n  0 to EXIT");
    printf("\n Enter : ");
    scanf("%d", &choice);

    if(choice == 0)     return 0;
	else if(choice == 1){
		printf(" Enter value : ");
		scanf("%d", &val);
        ins(&root, val);
	}
	else{	clear(); printf("INVALID entry! Retry\n");	}
    goto loop;
}

void ins(node **root, int val){
    if(*root == NULL){
        node *temp = (node *) malloc(sizeof(node));
        temp -> lkey = val;
		temp -> ukey = 0;
        temp -> lc = temp -> mc = temp -> rc = NULL;
		*root = temp;
		clear(); printf("-- %d INSERTED\n", val);
        return;
    }
	if(((*root) -> ukey) == 0){
		clear(); printf("-- %d INSERTED\n", val);
		if(val < ((*root) -> lkey)){
			(*root) -> ukey = (*root) -> lkey;
			(*root) -> lkey = val;
		}
		else	(*root) -> ukey = val;
	}
	else{
		if(val < ((*root) -> lkey))				ins(&((*root) -> lc), val);
		else if((val > ((*root) -> lkey)) && (val < ((*root) -> ukey)))
												ins(&((*root) -> mc), val);
		else if(val > ((*root) -> ukey))		ins(&((*root) -> rc), val);
		else	{	clear(); printf("DUPLICATE entry!\n");	}
	}
}

void inorder(node *root){
    if(root == NULL){
        printf("EMPTY TREE\n");
        return;
    }
    if(root -> lc != NULL)	inorder(root -> lc);
    printf("%d ", root -> lkey);
    if(root -> mc != NULL)	inorder(root -> mc);
    if(root -> ukey != 0)	printf("%d ", root -> ukey);
    if(root -> rc != NULL)	inorder(root -> rc);
}
