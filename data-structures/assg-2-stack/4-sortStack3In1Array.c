#include <stdio.h>
#include <stdlib.h>
#define SIZE 48

void push(int *, int, int *, int);
void pop(int *, int, int *, int*);
void display(int *, int, int);
int *stacks(int *, int *, int *);
void sort(int *, int *, int);
void push_sorted(int *, int *, int, int);
void temp_push(int *, int *, int);
int temp_pop(int *, int *);

int main(void){
	int top_1, top_2, top_3;
    int *stack = (int *) malloc(sizeof(int) * SIZE);
	stack = stacks(&top_1, &top_2, &top_3);
	//int stack[SIZE] = {7, 1, 2, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 2, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//top_1 = 4, top_2 = 19, top_3 = 36;

	sort(stack, &top_1, 1);
	sort(stack, &top_2, 2);
	sort(stack, &top_3, 3);

    int sorted[SIZE], sorted_top = -1;
	for(int i = 1; i <= 3; i++){
		int top;
		switch(i){
			case 1:	top = top_1; break;
			case 2:	top = top_2; break;
			case 3:	top = top_3; break;
		}
		while(top != ((i - 1) * (SIZE / 3) - 1))
			temp_push(sorted, &sorted_top, temp_pop(stack, &top));
	}
	sort(sorted, &sorted_top, 1);
	printf("\nSorted stack:");
	display(sorted, 1, sorted_top);
	printf("\n");

    return 0;
}

int *stacks(int *top_1, int *top_2, int *top_3)
{
    int *stack = (int *) malloc(sizeof(int) * SIZE);
    int stack_no, *curr_top, popped;
	*top_1 = -1, *top_2 = (SIZE / 3) - 1, *top_3 = 2 * (SIZE / 3) - 1;
    int choice, input, loop;
    do{
        printf("\n===========\n");
		printf("Enter Stack number : ");
		scanf("%d", &stack_no);
		switch(stack_no){
			case 1:	curr_top = top_1; break;
			case 2: curr_top = top_2; break;
			case 3: curr_top = top_3; break;
			default:
				printf("\nINVALID entry!\n");
				goto jump; break;
		}

		printf("\nPick operation:");
        printf("\n  1 to PUSH");
        printf("\n  2 to POP");
        printf("\n  3 to DISPLAY");
        printf("\n Enter : ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("\nEnter input : ");
                scanf("%d", &input);
                push(stack, stack_no, curr_top, input);
                break;
            case 2:
                pop(stack, stack_no, curr_top, &popped);
                break;
            case 3:
                display(stack, stack_no, *curr_top);
                break;
            default:
                printf("\nINVALID entry! Retry\n");
        }
		jump:	printf("\nEnter 0 to exit, 1 to continue : ");
		scanf("%d", &loop);
		if(loop == 0)	break;
    }while(1);

    return stack;
}

void push(int *stack, int stack_no, int *top, int data){
    if(*top == (stack_no * (SIZE / 3) - 1))
	printf("\n -- Stack Overflow\n");
    else{
        *(stack + (++(*top))) = data;
        printf("\n -- %d PUSHED into stack %d\n", data, stack_no);
    }
}

void pop(int *stack, int stack_no, int *top, int *popped){
    if(*top == ((stack_no - 1) * (SIZE / 3) -1))
	printf("\n -- Stack Underflow\n");
    else{
        *popped = *(stack + ((*top)--));
        printf("\n -- %d POPPED out of stack %d\n", *popped, stack_no);
    }
}

void display(int *stack, int stack_no, int top){
    printf("\n");
    if(top == ((stack_no - 1) * (SIZE / 3) - 1)){
        printf(" -- Empty Stack\n");
        return;
    }
    for(int i = top; i > ((stack_no - 1) * (SIZE / 3) - 1); i--)
        printf("  ||\t%d\n", stack[i]);
    printf("  --\n");
}

void sort(int *s, int *t, int stack_no){
	if(*t != ((stack_no - 1) * (SIZE / 3) - 1)){
		int temp = temp_pop(s, t);
		sort(s, t, stack_no);
		push_sorted(s, t, temp, stack_no);
	}
}

void push_sorted(int *s, int *t, int data, int stack_no){
	if((*t == ((stack_no - 1) * (SIZE / 3) - 1)) || (data < s[*t]))
		temp_push(s, t, data);
	else{
		int temp = temp_pop(s, t);
    	push_sorted(s, t, data, stack_no);
    	temp_push(s, t, temp);
	}
}

void temp_push(int *stack, int *top, int data){
    *(stack + (++(*top))) = data;
}

int temp_pop(int *stack, int *top){
    return *(stack + ((*top)--));
}
