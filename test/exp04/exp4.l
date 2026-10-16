%{
#include <stdio.h>
int vowels = 0, consonants = 0;
%}
%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z]     { consonants++; }
.|\n         { /* Ignore other characters */ }
%%
int yywrap(void) { return 1; }
int main(void) {
    printf("Enter a string:\n");
    yylex();
    printf("\nVowels = %d", vowels);
    printf("\nConsonants = %d\n", consonants);
    return 0;
}
