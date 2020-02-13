%{
    #include <stdio.h>

    int flag = 0;
%}

chars [A-Za-z0-9<>=!_]

%%
([A][N][D])|([a][n][d]) flag = 1;
([B][U][T])|([b][u][t]) flag = 1;
([O][R])|([o][r])       flag = 1;
{chars}+([A][N][D])|([a][n][d]){chars}+   ;
{chars}+([B][U][T])|([b][u][t]){chars}+   ;
{chars}+([O][R])|([o][r]){chars}+         ;
{chars}+                                  ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    if (flag == 1)
        printf("compound sentence\n");
    else
        printf("simple sentence\n");

    return 0;
}
