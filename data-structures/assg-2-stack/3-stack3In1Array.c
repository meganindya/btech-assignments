#include <stdio.h>
#define SIZE 48

void push(int *, int, int *, int);
void pop(int *, int, int *, int*);
void display(int *, int, int);

int main(void)
{
    int stack[SIZE], stack_no, top_1 = -1, top_2 = (SIZE / 3) - 1, top_3 = 2 * (SIZE / 3) - 1, *curr_top, popped;
    int choice, input, loop;
    do{
        printf("\n===========\n");
	printf("Enter Stack number : ");
	scanf("%d", &stack_no);
	switch(stack_no){
		case 1:	curr_top = &top_1; break;
		case 2: curr_top = &top_2; break;
		case 3: curr_top = &top_3; break;
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

    return 0;
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
