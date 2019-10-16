#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 64

void toPostfix(char *, char *);
void push(char *, int *, char);
char pop(char *, int *);
int priority(int);

int main(void){
    char exp[SIZE], infix_exp[SIZE + 2], postfix_exp[SIZE];
    printf("\nEnter INFIX expression : ");
    scanf("%s", exp);
    strcpy(&infix_exp[1], exp);
    infix_exp[0] = '('; infix_exp[strlen(exp) + 1] = ')';
    toPostfix(infix_exp, postfix_exp);
    printf("POSTFIX expression : ");
    for(int i = 0; postfix_exp[i] != '\0'; i++)
        printf("%c ", postfix_exp[i]);
    printf("\n\n");

    return 0;
}

void toPostfix(char *exp, char *postfix){
    char stack[SIZE]; int top = -1, ar_end = -1;
    for(int i = 0; exp[i] != '\0'; i++){
        if(isdigit(exp[i]))     push(postfix, &ar_end, exp[i]);
        else if(exp[i] == ')'){
            char temp;
            while((temp = pop(stack, &top)) != '(')
                push(postfix, &ar_end, temp);
        }
        else{
            if(exp[i] == '(')  goto jump;
	    	while((top != -1) && (priority(exp[i]) < priority(stack[top])))
			push(postfix, &ar_end, pop(stack, &top));
            jump:   push(stack, &top, exp[i]);
        }
    }
    push(postfix, &ar_end, '\0');
}

int priority(int operator){
	int temp;
	switch(operator){
		case '/':	temp = 4; break;
		case '*':       temp = 3; break;
		case '+':       temp = 2; break;
		case '-':       temp = 1; break;
	}
	return temp;
}

void push(char *stack, int *top, char data){
    *(stack + (++(*top))) = data;
}

char pop(char *stack, int *top){
    return *(stack + ((*top)--));
}
