%{
    #include <stdio.h>

    int c_idf = 0;
    int c_int = 0;
    int c_non = 0;
%}

%%
[\+|-]?[0-9]+               c_int++;
[a-zA-Z_][a-zA-Z0-9_]*      c_idf++;
[\.!@#$%|^&*=]*[a-zA-Z0-9_]*[\.!@#$%|^&*=]+[a-zA-Z0-9_]*[\.!@#$%|^&*=]* {
                            c_non++;
}
[0-9][a-zA-Z0-9_]*          c_non++;
^[^(a-zA-Z_)]+[a-zA-Z0-9_]* c_non++;
.                           ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("number of integers    : %d\n", c_int);
    printf("number of identifiers : %d\n", c_idf);
    printf("neither               : %d\n", c_non);

    return 0;
}
