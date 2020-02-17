%{
    #include <stdio.h>

    int c_printf = 0;
    int c_scanf  = 0;
%}

%%
printf {
    fprintf(yyout, "write");
    c_printf++;
}

scanf {
    fprintf(yyout, "read");
    c_scanf++;
}

.   ECHO;
%%

int main(int argc, char *argv[]) {
    yyin  = fopen("files/data-4.txt", "r");
    yyout = fopen("files/data-4-mod.txt", "w");

    yylex();

    printf("number of \'printf\' in file = %d\n", c_printf);
    printf("number of \'scanf\' in file  = %d\n", c_scanf);

    fclose(yyin);
    fclose(yyout);

    return 0;
}
