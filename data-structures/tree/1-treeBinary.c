#include <stdio.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

typedef struct tree{
	int data;
	struct tree *lc, *rc;
}	node;

void ins(node **, int);
node *del(node *, int);
void inorder(node *);
void preorder(node *);
void postorder(node *);
void traversal(node *);

int main(void){
	node *root = NULL; int choice, val;

	clear(); loop:
    traversal(root); printf("\n");
    printf("\n=====\nPick");
    printf("\n  1 for INSERTION");
    printf("\n  2 for DELETION");
    printf("\n 0 to EXIT\n");
    printf("\n Enter : ");
    scanf("%d", &choice);

    if(choice == 0)     return 0;
	if(choice == 1 || choice == 2){
		printf(" Enter Value : ");
		scanf("%d", &val);
	}
	switch(choice){
		case 1:
			ins(&root, val); break;
		case 2:
			if(root == NULL){
				clear(); printf("NOTHING TO DELETE\n");
			}
			else{
				clear(); printf("%d DELETED\n", val);
				root = del(root, val);
			}
			break;
		default:
			clear(); printf("INVALID entry! Retry\n");
	}
    goto loop;
}

void ins(node **r, int v){
	if(*r == NULL){
		node *temp = (node *) malloc(sizeof(node));
		temp -> data = v;
		temp -> lc = temp -> rc = NULL;
		*r = temp;
		clear(); printf("-- %d INSERTED\n", v);
	}
	else if(v < ((*r) -> data))
		ins(&((*r) -> lc), v);
	else if(v > ((*r) -> data))
		ins(&((*r) -> rc), v);
	else{
		clear(); printf("DUPLICATE entry!\n");
	}
}

node *del(node *r, int v){
	if(r == NULL)	return r;
	else if(v < r -> data)
		r -> lc = del(r -> lc, v);
	else if(v > r -> data)
		r -> rc = del(r -> rc, v);
	else{
		if(r -> lc == NULL){
			node *temp = r -> rc;
			free(r); return temp;
		}
		else if(r -> rc == NULL){
			node *temp = r -> lc;
			free(r); return temp;
		}
		node *temp = r -> rc;
		while(temp -> lc != NULL)	temp = temp -> lc;
		r -> data = temp -> data;
		r -> rc = del(r -> rc, temp -> data);
	}
	return r;
}

void traversal(node *r){
	if(r == NULL)   {   printf("EMPTY TREE"); return;   }
	printf("\nINORDER   : "); inorder(r);
	printf("\nPREORDER  : "); preorder(r);
	printf("\nPOSTORDER : "); postorder(r);
}

void inorder(node *r){
	if((r -> lc) != NULL)	inorder(r -> lc);
	printf(" %d ", (r -> data));
	if((r -> rc) != NULL)	inorder(r -> rc);
}

void preorder(node *r){
	printf(" %d ", (r -> data));
	if((r -> lc) != NULL)	preorder(r -> lc);
	if((r -> rc) != NULL)	preorder(r -> rc);
}

void postorder(node *r){
	if((r -> lc) != NULL)	postorder(r -> lc);
	if((r -> rc) != NULL)	postorder(r -> rc);
	printf(" %d ", (r -> data));
}
