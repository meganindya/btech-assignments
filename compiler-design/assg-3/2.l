%{
    #include <stdio.h>

    int pi = 0;
    int ni = 0;
    int pf = 0;
    int nf = 0;
%}

%%
[\+]?[0-9]+         pi++;
[-][0-9]+           ni++;

[\+]?[0-9]*[\.][0-9]+                       pf++;
[\+]?[0-9]*[\.][0-9]+[\.][0-9]*             ;
[\+]?[0-9]*[\.][0-9]+[e|E][\+|-]?[0-9]+     pf++;
[\+]?[0-9]+[e|E][\+|-]?[0-9]+               pf++;

[-][0-9]*[\.][0-9]+                         nf++;
[-][0-9]*[\.][0-9]+[\.][0-9]*               ;
[-][0-9]*[\.][0-9]+[e|E][\+|-]?[0-9]+       nf++;
[-][0-9]+[e|E][\+|-]?[0-9]+                 nf++;

.                   ;
%%

int yywrap() {}
int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("number of Positive Integers  : %d\n", pi);
    printf("number of Negative Integers  : %d\n", ni);
    printf("number of Positive Fractions : %d\n", pf);
    printf("number of Negative Fractions : %d\n", nf);

    return 0;
}
