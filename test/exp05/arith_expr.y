%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(const char *s);
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS
%%
stmt: expr '\n' { printf("Valid Expression\n"); } ;
expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '-' expr %prec UMINUS
    | '(' expr ')'
    | NUMBER
    ;
%%
int yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
    return 1;
}
int main(void) {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}
