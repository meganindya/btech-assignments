%{
    #include <stdio.h>

    int flag = 0;
%}

%%
[a][b][b][A-Za-z0-9]*[c][d][d]                          flag = 1;
[A-Za-z0-9]+[a][b][b][A-Za-z0-9]*[c][d][d][A-Za-z0-9]+  ;
[a][b][b][A-Za-z0-9]*[c][d][d][A-Za-z0-9]+              ;
[A-Za-z0-9]+[a][b][b][A-Za-z0-9]*[c][d][d]              ;
[A-Za-z0-9]*                                            ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    if (flag == 1)
        printf("starts with 'abb', ends with 'cdd'\n");
    else
        printf("invalid\n");

    return 0;
}
