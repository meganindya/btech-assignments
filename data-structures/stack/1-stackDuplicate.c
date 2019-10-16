#include <stdio.h>
#include <stdlib.h>

int *duplicateStack(int *, int);
void push(int *, int *, int);
int pop(int *, int *);

int main(void){
	int size;
	printf("\nEnter length of Stack : ");
	scanf("%d", &size);
	int stack[size];
	printf("\nEnter Stack elements from top to bottom:\n");
	for(int i = (size - 1); i >= 0; i--){
		scanf("%d", &stack[i]);
	}
	int *p;
	p = duplicateStack(stack, size);
	printf("\nDuplicate Stack:\n");
	for(int i = (size - 1); i >= 0; i--)
    		printf("%d\n", *(p + i));
	printf("\n");

    return 0;
}

int *duplicateStack(int *stack, int size){
	int top = size - 1;
	int *temp = (int *) malloc(sizeof(int) * size), top_temp = -1;
	int *duplicate = (int *) malloc(sizeof(int) * size), top_dup = -1;

	for(int i = 0; i < size; i++)
		push(temp, &top_temp, pop(stack, &top));
	for(int i = 0; i < size; i++){
		int popped = pop(temp, &top_temp);
		push(duplicate, &top_dup, popped);
		push(stack, &top, popped);
	}

	return &duplicate[0];
}

void push(int *stack, int *top, int data){
    *(stack + (++(*top))) = data;
}

int pop(int *stack, int *top){
    return *(stack + ((*top)--));
}
