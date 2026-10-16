#include <stdio.h>
int main(void) {
  int n, i;
  char op[10][2], a[10][10], b[10][10], r[10][10];
  printf("Enter number of instructions: ");
  scanf("%d", &n);
  printf("Enter TAC:\n");
  for (i = 0; i < n; i++)
    scanf("%1s %9s %9s %9s", op[i], a[i], b[i], r[i]);
  printf("\n8086 Assembly Code:\n");
  for (i = 0; i < n; i++) {
    if (op[i][0] == '+') {
      printf("MOV AX,%s\n", a[i]);
      printf("ADD AX,%s\n", b[i]);
      printf("MOV %s,AX\n\n", r[i]);
    } else if (op[i][0] == '-') {
      printf("MOV AX,%s\n", a[i]);
      printf("SUB AX,%s\n", b[i]);
      printf("MOV %s,AX\n\n", r[i]);
    } else if (op[i][0] == '*') {
      printf("MOV AX,%s\n", a[i]);
      printf("MOV BX,%s\n", b[i]);
      printf("MUL BX\n");
      printf("MOV %s,AX\n\n", r[i]);
    } else if (op[i][0] == '/') {
      printf("MOV AX,%s\n", a[i]);
      printf("MOV BX,%s\n", b[i]);
      printf("DIV BX\n");
      printf("MOV %s,AX\n\n", r[i]);
    }
  }
  return 0;
}
