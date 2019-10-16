#include <stdio.h>
#include <stdlib.h>
#define SIZE 16
#define clear() printf("\033[H\033[J")
//#define clear() system("cls")

void traverse(int *, int);
void inorder(int *, int);
void ins(int *, int *, int);
void del(int *, int *, int);
void push(int *, int *, int);
int pop(int *, int *);

int main(void){
	int bst[SIZE][3], z = -1, choice, value;
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < 3; j++)
			bst[i][j] = 0;
	clear();
	loop:	traverse(&bst[0][0], z);
	printf("\n\n Pick\n =====\n");
	printf("  1 to INSERT\n");
	printf("  2 to DELETE\n");
	printf(" 0 to EXIT\n");
	printf("\n Enter : ");
	scanf("%d", &choice);

	if(choice == 0)	return 0;
	if(choice == 1 || choice == 2){
		printf(" Enter Value : ");
		scanf("%d", &value);
	}
	switch(choice){
		case 1:
			if(z == (SIZE - 1)){	clear(); printf(" Can't INSERT More\n");	}
			else ins(&bst[0][0], &z, value);
			break;
		case 2:
			if(z == -1){	clear(); printf(" Nothing to DELETE\n");	}
			else del(&bst[0][0], &z, value);
			break;
		default:
			clear(); printf(" INVALID entry! Retry\n");
			break;
	}
	goto loop;
}

void ins(int *bst, int *z, int v){
	clear(); int par = *(bst + 1), index = 0;
	if(*z == -1){
		*(bst + 3 * (++(*z)) + 1) = v;
		*(bst + 3 * (*z) + 0) = *(bst + 3 * (*z) + 2) = -1;
		printf("-- %d INSERTED\n", v); return;
	}
	while(1){
		if(v == par){
			printf(" DUPLICATE Value\n");
			break;
		}
		else{
			int ch, cc;
			if(v < par)		{	ch = *(bst + 3 * index + 0); cc = 0;  }
			else if(v > par){	ch = *(bst + 3 * index + 2); cc = 2;  }
			if(ch != -1){
				par = *(bst + 3 * ch + 1);
				index = ch;
			}
			else{
				*(bst + 3 * (++(*z)) + 1) = v;
				*(bst + 3 * (*z) + 0) = *(bst + 3 * (*z) + 2) = -1;
				printf("-- %d INSERTED\n", v);
				*(bst + 3 * index + cc) = *z; break;
			}
		}
	}
}

void del(int *bst, int *z, int v){
	clear(); int index, f = 1;
	for(int i = 0; i <= *z; i++)
		if(*(bst + 3 * i + 1) == v){
			index = i; f = 0; break;
		}
	if(f == 1)	{	printf(" %d Not Found\n", v); return;	}
	if(*z == 0){
		*(bst + 0) = *(bst + 1) = *(bst + 2) = 0;
		(*z)--; goto skip;
	}
	if(*(bst + 3 * index + 0) == -1 && *(bst + 3 * index + 2) == -1){
		for(int i = 0; i <= *z; i++){
			if(*(bst + 3 * i + 0) == index){
				*(bst + 3 * i + 0) = -1; break;
			}
			if(*(bst + 3 * i + 2) == index){
				*(bst + 3 * i + 2) = -1; break;
			}
		}
	}
	else if(*(bst + 3 * index + 0) == -1 && *(bst + 3 * index + 2) != -1){
		int temp = *(bst + 3 * index + 2);
		for(int i = 0; i <= *z; i++){
			if(*(bst + 3 * i + 0) == index){
				*(bst + 3 * i + 0) = temp; break;
			}
			if(*(bst + 3 * i + 2) == index){
				*(bst + 3 * i + 2) = temp; break;
			}
		}
	}
	else if(*(bst + 3 * index + 0) != -1 && *(bst + 3 * index + 2) == -1){
		int temp = *(bst + 3 * index + 0);
		for(int i = 0; i <= *z; i++){
			if(*(bst + 3 * i + 0) == index){
				*(bst + 3 * i + 0) = temp; break;
			}
			if(*(bst + 3 * i + 2) == index){
				*(bst + 3 * i + 2) = temp; break;
			}
		}
	}
	else{
		int temp = *(bst + 3 * index + 0);
		while(*(bst + 3 * temp + 2) != -1)
			temp = *(bst + 3 * temp + 2);
		if(temp == *(bst + 3 * index + 0))
			*(bst + 3 * index + 0) = -1;
		*(bst + 3 * index + 1) = *(bst + 3 * temp + 1);
		*(bst + 3 * temp + 1) = v;
		del(bst, z, v); return;
	}
	for(int i = index; i < *z; i++)
		for(int j = 0; j < 3; j++)
			*(bst + 3 * i + j) = *(bst + 3 * (i + 1) + j);
	for(int i = 0; i < 3; i++)
		*(bst + 3 * (*z) + i) = 0;
	for(int i = 0; i < index; i++)
		for(int j = 0; j < 3; j += 2)
			if(*(bst + 3 * i + j) > index)	(*(bst + 3 * i + j))--;
	(*z)--; skip: printf("-- %d DELETED\n", v);
}

void traverse(int *bst, int z){
	printf("\n");
	for(int i = 0; i < SIZE; i++){
		printf(" %d\t", i);
		for(int j = 0; j < 3; j++)
			printf("%d  ", *(bst + 3 * i + j));
		printf("\n");
	}
	if(z == -1) {	printf("\n EMPTY TREE");	return;	}
	printf("\n INORDER :  ");
	inorder(bst, 0);
}

void inorder(int *bst, int z){
	int stack[SIZE], inor[SIZE], top_s = -1, top_i = -1, index = z;
    while(index != -1){
        push(stack, &top_s, index);
        index = *(bst + 3 * index + 0);
    }
    while(top_s != -1){
        index = pop(stack, &top_s);
        printf("%d ", *(bst + 3 * index + 1));
        inorder(bst, *(bst + 3 * index + 2));
    }
}

void push(int *stack, int *top, int v){
	stack[++(*top)] = v;
}

int pop(int *stack, int *top){
	return stack[(*top)--];
}
