%{
    #include <stdio.h>

    int chars = 0;
    int words = 0;
    int spacs = 0;
    int lines = 0;
%}

%%
[ \t]           spacs++;

[\n]            {
    lines++;
    chars--;
}

[a-zA-Z0-9]+    {
    words++;
    chars += yyleng;
}

[^a-zA-Z0-9 \t] chars++;
%%

int main(int argc, char *argv[]) {
    printf("Input: ");
    yylex();

    printf("number of characters:   %d\n", chars);
    printf("number of spaces:       %d\n", spacs);
    printf("number of lines:        %d\n", lines + 1);
    printf("number of words:        %d\n", words);

    return 0;
}
