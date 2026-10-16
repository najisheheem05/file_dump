#include <ctype.h>
#include <stdio.h>
#include <string.h>
char stack[20][10];
int top = -1, temp = 1;
void push(char s[]) { strcpy(stack[++top], s); }
char *pop(void) { return stack[top--]; }
int prec(char c) {
  if (c == '+' || c == '-')
    return 1;
  if (c == '*' || c == '/')
    return 2;
  if (c == '^')
    return 3;
  return 0;
}
int main(void) {
  char infix[30], postfix[30], a[10], b[10], t[10];
  int i, j = 0;
  printf("Enter expression: ");
  scanf("%29s", infix);
  for (i = 0; infix[i]; i++) {
    if (isalnum((unsigned char)infix[i]))
      postfix[j++] = infix[i];
    else if (infix[i] == '(') {
      char x[2] = "(";
      push(x);
    } else if (infix[i] == ')') {
      while (top != -1 && strcmp(stack[top], "(") != 0)
        postfix[j++] = pop()[0];
      if (top != -1)
        pop();
    } else {
      while (top != -1 && prec(stack[top][0]) >= prec(infix[i]))
        postfix[j++] = pop()[0];
      char x[2] = {infix[i], '\0'};
      push(x);
    }
  }
  while (top != -1)
    postfix[j++] = pop()[0];
  postfix[j] = '\0';
  printf("Postfix form: %s\n", postfix);
  top = -1;
  printf("\nIntermediate Code:\n");
  for (i = 0; postfix[i]; i++) {
    if (isalnum((unsigned char)postfix[i])) {
      char x[2] = {postfix[i], '\0'};
      push(x);
    } else {
      strcpy(b, pop());
      strcpy(a, pop());
      sprintf(t, "t%d", temp);
      printf("%s = %s %c %s\n", t, a, postfix[i], b);
      push(t);
      temp++;
    }
  }
  return 0;
}
