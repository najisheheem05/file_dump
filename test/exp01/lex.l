
%{
#include <stdio.h>
%}
letter [a-zA-Z_]
digit [0-9]
%%
int|float|char|double|void|if|else|while|do|for|return|break|continue|switch|case|default|struct { printf("%s\tKeyword\n", yytext); }
{letter}({letter}|{digit})* { printf("%s\tIdentifier\n", yytext); }
{digit}+"."{digit}+ { printf("%s\tFloat constant\n", yytext); }
{digit}+ { printf("%s\tInteger constant\n", yytext); }
"=="|"!="|"<="|">="|"++"|"--"|"+="|"-="|"*="|"/="|"&&"|"||" { printf("%s\tOperator\n", yytext); }
[+*/%=<>!&|-] { printf("%s\tOperator\n", yytext); }
[(){};,] { printf("%s\tSpecial symbol\n", yytext); }
[ \t\n]+ ;
. { printf("%s\tUnknown\n", yytext); }
%%
int yywrap(void) { return 1; }
int main(void) {
    extern FILE *yyin;
    yyin = fopen("input_lex.c", "r");
    if (yyin == NULL) { printf("Error opening file\n"); return 1; }
    yylex();
    fclose(yyin);
    return 0;
}
