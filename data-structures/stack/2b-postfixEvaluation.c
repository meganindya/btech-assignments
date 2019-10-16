#include <stdio.h>
#include <ctype.h>
#define SIZE 64

int postfix_eval(char *);
void push(int *, int *, int);
int pop(int *, int *);

int main(void){
    char expression[SIZE]; int answer;
    printf("\nEnter POSTFIX expression : ");
    scanf("%s", expression);
    answer = postfix_eval(expression);
    printf("Answer : %d\n\n", answer);

    return 0;
}

int postfix_eval(char *exp){
    int stack[SIZE], top = -1, operand1, operand2, result;
    for(int i = 0; exp[i] != '\0'; i++){
        if(isdigit(exp[i]))     push(stack, &top, (exp[i] - '0'));
        else{
            operand1 = pop(stack, &top);
            operand2 = pop(stack, &top);

            switch(exp[i]){
                case '+':     result = operand2 + operand1; break;
                case '-':     result = operand2 - operand1; break;
                case '*':     result = operand2 * operand1; break;
                case '/':     result = operand2 / operand1; break;
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
