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
input: input line | /* empty */ ;
line: expr '\n' { printf("Result = %d\n", $1); } ;
expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr {
        if ($3 == 0) { yyerror("Division by zero"); YYABORT; }
        else { $$ = $1 / $3; }
      }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;
%%
int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 1;
}
int main(void) {
    printf("Enter expressions to evaluate (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}
