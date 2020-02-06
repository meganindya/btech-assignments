%{
    #include <stdio.h>
    #include <string.h>

    int c_printf = 0;
    int c_scanf = 0;
%}


%%
[a-zA-Z]+ {
    if (strcmp(yytext, "printf") == 0)
        c_printf++;
    if (strcmp(yytext, "scanf") == 0)
        c_scanf++;
}

. ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("Number of \'printf\': %d\n", c_printf);
    printf("Number of \'scanf\': %d\n", c_scanf);

    return 0;
}
