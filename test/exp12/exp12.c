#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct expr {
  char op[2], op1[5], op2[5], res[5];
  int flag;
} arr[10];
int n;
void input(void);
void output(void);
void change(int p, char *res);
void constant(void);
int main(void) {
  input();
  constant();
  output();
  return 0;
}
void input(void) {
  int i;
  printf("\nEnter the maximum number of expressions: ");
  scanf("%d", &n);
  printf("\nEnter the input:\n");
  for (i = 0; i < n; i++) {
    scanf("%1s %4s %4s %4s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    arr[i].flag = 0;
  }
}
void constant(void) {
  int i, op1, op2, res;
  char op, res1[5];
  for (i = 0; i < n; i++) {
    if ((isdigit((unsigned char)arr[i].op1[0]) &&
         isdigit((unsigned char)arr[i].op2[0])) ||
        strcmp(arr[i].op, "=") == 0) {
      op1 = atoi(arr[i].op1);
      op2 = atoi(arr[i].op2);
      op = arr[i].op[0];
      switch (op) {
      case '+':
        res = op1 + op2;
        break;
      case '-':
        res = op1 - op2;
        break;
      case '*':
        res = op1 * op2;
        break;
      case '/':
        if (op2 == 0)
          continue;
        res = op1 / op2;
        break;
      case '=':
        res = op1;
        break;
      default:
        continue;
      }
      snprintf(res1, sizeof(res1), "%d", res);
      arr[i].flag = 1;
      change(i, res1);
    }
  }
}
void change(int p, char *res) {
  int i;
  for (i = p + 1; i < n; i++) {
    if (strcmp(arr[p].res, arr[i].op1) == 0)
      strcpy(arr[i].op1, res);
    if (strcmp(arr[p].res, arr[i].op2) == 0)
      strcpy(arr[i].op2, res);
  }
}
void output(void) {
  int i;
  printf("\nOptimized code is:");
  for (i = 0; i < n; i++) {
    if (!arr[i].flag)
      printf("\n%s %s %s %s", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
  }
  printf("\n");
}
