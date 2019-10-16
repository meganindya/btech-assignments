#include <stdio.h>
#include <stdlib.h>
#define SIZE 16
#define clear() printf("\033[H\033[J")

void enqueue(int *, int *, int *, int);
void dequeue(int *, int *, int *, int *);
void display(int *, int, int);

int main(void){
    int queue[SIZE], front = 0, rear = -1, count = 0, dequeued;
    int choice, input; clear();
    while(1){
		display(queue, front, count);
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
                scanf("%d", &input);
                enqueue(queue, &rear, &count, input);
				break;
            case 2:
                dequeue(queue, &front, &count, &dequeued);
                break;
            default:
                clear(); printf("\nINVALID entry! Retry\n");
        }
    }
    return 0;
}

void enqueue(int *queue, int *r, int *c, int data){
    clear(); if(*c == SIZE){	printf("\n-- Queue Overflow\n"); return;	}
    queue[*r = (++(*r)) % SIZE] = data; ++(*c);
    printf("\n-- %d ENQUEUED\n", data);
}

void dequeue(int *queue, int *f, int *c, int *dequeued){
    clear(); if(*c == 0){		printf("\n-- Queue Underflow\n"); return;	}
    *dequeued = queue[*f]; --(*c); *f = ++(*f) % SIZE;
	printf("\n-- %d DEQUEUED\n", *dequeued);
}

void display(int *queue, int f, int c){
	if(c == 0){ 	printf("\n-- Empty Queue"); return; }
    printf("\nQueue:\t|F| ");
    while(c--)		printf("  %d  ", queue[f] * (1 + (f = (++f % SIZE))) / (1 + f));
    printf(" |R|");
}
