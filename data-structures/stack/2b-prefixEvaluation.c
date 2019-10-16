#include <stdio.h>
#include <ctype.h>
#define SIZE 64

int prefix_eval(char *);
void push(int *, int *, int);
int pop(int *, int *);

int main(void){
    char expression[SIZE]; int answer;
    printf("\nEnter PREFIX expression : ");
    scanf("%s", expression);
    answer = prefix_eval(expression);
    printf("Answer : %d\n\n", answer);

    return 0;
}

int prefix_eval(char *exp){
    int stack[SIZE], top = -1, operand1, operand2, result, length = 0;
    for(length = 0; exp[length] != '\0'; length++);
    for(int i = (length -1); i >= 0; i--){
        if(isdigit(exp[i]))     push(stack, &top, (exp[i] - '0'));
        else{
            operand1 = pop(stack, &top);
            operand2 = pop(stack, &top);

            switch(exp[i]){
                case '+':     result = operand1 + operand2; break;
                case '-':     result = operand1 - operand2; break;
                case '*':     result = operand1 * operand2; break;
                case '/':     result = operand1 / operand2; break;
            }
            push(stack, &top, result);
        }
    }
    if(top == -1)   return 0;
    else            return stack[top];
}

void push(int *stack, int *top, int data){
    *(stack + (++(*top))) = data;
}

int pop(int *stack, int *top){
    return *(stack + ((*top)--));
}
