%{
    #include <stdio.h>

    int c_vowel = 0;
    int c_const = 0;
%}


%%
[aeiouAEIOU]    c_vowel++;
[a-zA-Z]        c_const++;
.               ;
%%

int main(int argc, char *argv[]) {
    printf("Enter string: ");
    yylex();

    printf("Number of vowels:     %d\n", c_vowel);
    printf("Number of consonants: %d\n", c_const);

    return 0;
}
