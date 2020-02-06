%{
    #include <stdio.h>

    int v_count = 0;
    int c_count = 0;
%}


%%
[aeiouAEIOU] {
    v_count++;
}

[a-zA-Z] {
    c_count++;
}

. ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("Number of vowels: %d\n", v_count);
    printf("Number of consonants: %d\n", c_count);

    return 0;
}
