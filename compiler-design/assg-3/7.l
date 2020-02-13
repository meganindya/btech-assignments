%{
    #include <stdio.h>

    int single = 0;
    int multi  = 0;
%}

%%
\/\/.*\n            single++;
\/\*(.*\n)*.*\*\/   multi++;
%%

int main(int argc, char *argv[]) {
    yyin = fopen("data-7.txt", "r");
    yyout = fopen("data-7-mod.txt", "w");
    yylex();

    printf("number of single line comments: %d\n", single);
    printf("number of multi line comments:  %d\n", multi);

    return 0;
}
