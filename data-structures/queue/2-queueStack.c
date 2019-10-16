#include <stdio.h>
#include <stdlib.h>
#define SIZE 6
#define clear() printf("\033[H\033[J");

void enqueue(int *, int *, int *, int *, int *, int);
void dequeue(int *, int *, int *, int *, int *, int *);
void display(int *, int *, int *, int *, int);
void push(int *, int *, int);
int pop(int *, int *);

int main(void){
    int input[SIZE], output[SIZE], ip_top = -1, op_top = -1, count = 0, choice, data, out; clear();
    while(1){
        display(input, &ip_top, output, &op_top, count);
        printf("\n=====\nPick");
        printf("\n  1 to ENQUEUE");
        printf("\n  2 to DEQUEUE");
        printf("\n0 to exit\n");
        printf("\n Enter : ");
        scanf("%d", &choice);

        if(choice == 0)     break;
        switch(choice){
            case 1:
                printf(" Enter input : ");
                scanf("%d", &data);
                enqueue(input, &ip_top, output, &op_top, &count, data);
                break;
            case 2:
                dequeue(input, &ip_top, output, &op_top, &count, &out);
                break;
            default:
                clear(); printf("\nINVALID entry! Retry\n");
        }
    }
    return 0;
}

void enqueue(int *ip_stack, int *ip_top, int *op_stack, int *op_top, int *count, int data){
    clear(); if(*count == SIZE){	printf("\n-- Queue Overflow\n"); return;  }
    while(*op_top != -1)    		push(ip_stack, ip_top, pop(op_stack, op_top));
    push(ip_stack, ip_top, data); (*count)++;
    printf("\n-- %d ENQUEUED\n", *(ip_stack + *ip_top));
}

void dequeue(int *ip_stack, int *ip_top, int *op_stack, int *op_top, int *count, int *out){
    clear(); if(*count == 0){       printf("\n-- Queue Underflow\n"); return;  }
    while(*ip_top != -1)    		push(op_stack, op_top, pop(ip_stack, ip_top));
    printf("\n-- %d DEQUEUED\n", (*out = pop(op_stack, op_top))); (*count)--;
}

void display(int *ip_stack, int *ip_top, int *op_stack, int *op_top, int count){
    if(count == 0){        printf("\n-- Empty Queue"); return;   }
    while(*ip_top != -1)   push(op_stack, op_top, pop(ip_stack, ip_top));
    printf("\nQueue:\t|F| "); int temp;
    while(*op_top != -1){
        printf("  %d  ", (temp = pop(op_stack, op_top)));
        push( ip_stack, ip_top, temp);
    }   printf(" |R|");
}

void push(int *stack, int *top, int data){
    *(stack + (++(*top))) = data;
}

int pop(int *stack, int *top){
    return *(stack + ((*top)--));
}
