%{
#include <stdio.h>
int lines = 0, words = 0, chars = 0;
%}
%%
\n          { lines++; chars++; }
[ \t]+      { chars += yyleng; }
[^ \t\n]+    { words++; chars += yyleng; }
%%
int yywrap(void) { return 1; }
int main(void) {
    printf("Enter text (Ctrl+D to end):\n");
    yylex();
    printf("\nLines = %d", lines);
    printf("\nWords = %d", words);
    printf("\nCharacters = %d\n", chars);
    return 0;
}
