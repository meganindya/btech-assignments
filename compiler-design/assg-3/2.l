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
([\+]?[0-9]*([\.][0-9]+)[e|E][\+|-]?[0-9]+) pf++;
([\+]?[0-9]+[e|E][\+|-]?[0-9]+)             pf++;

[-][0-9]*\.[0-9]+                           nf++;
[-]?[0-9]*[\.][0-9]+[\.][0-9]*              ;
[-][0-9]*([\.][0-9]+)[e|E][\+|-]?[0-9]+     nf++;
[-]?[0-9]+[e|E][\+|-]?[0-9]+                nf++;

.                   ;
\n                  return 0;
%%

int yywrap() {}
int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("Number of Positive integers: %d\n", pi);
    printf("Number of Negative integers: %d\n", ni);
    printf("Number of Positive fractions: %d\n", pf);
    printf("Number of Negative fractions: %d\n", nf);

    return 0;
}

/*
[A-Za-z0-9!@#$%^&*()~`:;"',.\/<>\\\|\+\-]+ {;}
*/
