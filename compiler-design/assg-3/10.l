%{
    #include <stdio.h>

    int flag = 0;
%}


%%
" AND "|" and " flag = 1;
" BUT "|" but " flag = 1;
" OR "|" or "   flag = 1;
.               ;
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
