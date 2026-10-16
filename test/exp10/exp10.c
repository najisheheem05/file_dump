#include <stdio.h>
#include <string.h>
char s[20];
int i = 0, error = 0;
void E(void);
void T(void);
void F(void);
void E(void) {
  T();
  while (s[i] == '+') { /* corrected malformed condition in PDF */
    i++;
    T();
  }
}
void T(void) {
  F();
  while (s[i] == '*') {
    i++;
    F();
  }
}
void F(void) {
  if (s[i] == 'a')
    i++;
  else if (s[i] == '(') {
    i++;
    E();
    if (s[i] == ')')
      i++;
    else
      error = 1;
  } else
    error = 1;
}
int main(void) {
  printf("Enter expression: ");
  scanf("%19s", s);
  E();
  if (i == (int)strlen(s) && error == 0)
    printf("Accepted");
  else
    printf("Rejected");
  return 0;
}
