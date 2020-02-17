%{
    #include <stdio.h>

    int c_printf = 0;
    int c_scanf  = 0;
%}

%%
printf      c_printf++;
scanf       c_scanf++;
.           ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("number of \'printf\' : %d\n", c_printf);
    printf("number of \'scanf\'  : %d\n", c_scanf);

    return 0;
}
