#include <stdio.h>
char stack[50], s[50];
int top = -1, i = 0;
char op[] = {'i', '+', '*', '$'};
char table[4][4] = {{'=', '>', '>', '>'},
                    {'<', '>', '<', '>'},
                    {'<', '>', '>', '>'},
                    {'<', '<', '<', '='}};
int pos(char c) {
  int j;
  for (j = 0; j < 4; j++)
    if (op[j] == c)
      return j;
  return -1;
}
void display(void) {
  int j;
  for (j = 0; j <= top; j++)
    printf("%c", stack[j]);
  printf("\t\t");
  for (j = i; s[j] != '\0'; j++)
    printf("%c", s[j]);
  printf("\t\t");
}
void parse(void) {
  char rel, ch;
  int p1, p2;
  printf("Enter the expression for operator precedence parsing(end with $): ");
  scanf("%49s", s);
  stack[++top] = '$';
  while (1) {
    display();
    if (stack[top] == '$' && s[i] == '$') {
      printf("\nValid Expression\n");
      return;
    }
    p1 = pos(stack[top]);
    p2 = pos(s[i]);
    if (p1 == -1 || p2 == -1) {
      printf("\nInvalid expression\n");
      return;
    }
    rel = table[p1][p2];
    if (rel == '<' || rel == '=') {
      stack[++top] = s[i++];
      printf("Shift\n");
    } else if (rel == '>') {
      ch = stack[top--];
      while (top >= 0 && pos(stack[top]) != -1 &&
             table[pos(stack[top])][pos(ch)] != '<') {
        ch = stack[top--];
      }
      printf("%c Reduce\n", ch);
    } else {
      printf("\nInvalid expression\n");
      return;
    }
  }
}
int main(void) {
  parse();
  return 0;
}
