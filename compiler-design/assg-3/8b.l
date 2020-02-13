%{
    #include <stdio.h>

    int flag = 0;
%}

%%
[a-zA-Z0-9]*([a][b])+[a-zA-Z0-9]*   flag = 1;
[a-zA-Z0-9]+                        ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    if (flag == 1)
        printf("contains 'ab'\n");
    else
        printf("doesn't contain 'ab'\n");

    return 0;
}
