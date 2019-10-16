#include <stdio.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

int *input(int*);
int stackPerm(int *, int *, int);
int pop(int *, int *);
void push(int *, int *, int);
void enqueue(int *, int *, int *, int, int);
void dequeue(int *, int *, int *, int *, int);

int main(void){
    int *orig, *perm, count = 0; clear();
    perm = input(&count);
    orig = (int *) malloc(sizeof(int) * count);
    printf("  Original ->\t");
    for(int i = 0; i < count; i++)  printf("%d ", (orig[i] = i + 1));
    if(stackPerm(orig, perm, count) == 1)
            printf("\n\n::Sequence IS a Stack Permutation\n\n");
    else    printf("\n\n::Sequence IS NOT a Stack Permutation\n\n");
    return 0;
}

int *input(int *count){
	printf("Enter permuted sequence, elements separated by ' ':\n  Sequence ->\t");
    char sequence[256]; scanf("%[^\n]s", sequence);
    int temp = 0, elements[256];
	for(int i = 0; sequence[i] != '\0'; i++){
		if(sequence[i] == ' '){	elements[(*count)++] = temp; temp = 0;  }
        else                    temp = (10 * temp) + sequence[i] - '0';
    }   elements[(*count)++] = temp;
    int *permuted = (int *) malloc(sizeof(int) * *count);
    for(int i = 0; i < *count; i++) permuted[i] = elements[i];
	return permuted;
}

int stackPerm(int *orig, int *perm, int count){
    int P[count], Q[count], S[count], f = 0, temp, index = 0;
    int p_front = 0, p_count = count, q_rear = -1, q_count = 0, s_top = -1;
    for(int i = 0; i < count; i++)  P[i] = orig[i];
    while(p_count != 0){
        dequeue(P, &p_front, &p_count, &temp, count);
        if(temp == perm[index]){
            enqueue(Q, &q_rear, &q_count, temp, count); index++;
            while(s_top != -1){
                if(S[s_top] == perm[index++])
                    enqueue(Q, &q_rear, &q_count, pop(S, &s_top), count);
                else    break;
            }
        }
        else    push(S, &s_top, temp);
    }   if(q_count == count)    f = 1;
    return f;
}

void enqueue(int *queue, int *rear, int *count, int data, int SIZE){
    queue[*rear = (++(*rear)) % SIZE] = data * (++(*count)) / (*count);
}

void dequeue(int *queue, int *front, int *count, int *dequeued, int SIZE){
    *dequeued = queue[*front]; *front = (++(*front) % SIZE) * (*count) / ((*count)--);
}

void push(int *stack, int *top, int data){
    *(stack + (++(*top))) = data;
}

int pop(int *stack, int *top){
    return *(stack + ((*top)--));
}
