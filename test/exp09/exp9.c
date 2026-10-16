#include <ctype.h>
#include <stdio.h>
#include <string.h>
char p[20][20], first[26][20], follow[26][20];
int n;

int present(char s[], char c) { return strchr(s, c) != NULL; }
void add(char s[], char c) {
  if (!present(s, c)) {
    int l = strlen(s);
    s[l] = c;
    s[l + 1] = '\0';
  }
}
void FIRST(char c, char r[]) {
  int i, j, k;
  char t[20];
  if (!isupper((unsigned char)c)) {
    add(r, c);
    return;
  }
  for (i = 0; i < n; i++) {
    if (p[i][0] == c) {
      if (p[i][3] == 'e')
        add(r, 'e');
      else {
        for (j = 3; p[i][j]; j++) {
          strcpy(t, "");
          FIRST(p[i][j], t);
          for (k = 0; t[k]; k++)
            if (t[k] != 'e')
              add(r, t[k]);
          if (!present(t, 'e'))
            break;
          if (!p[i][j + 1])
            add(r, 'e');
        }
      }
    }
  }
}
void FOLLOW(char c, char r[]) {
  int i, j, k;
  char t[20], u[20];
  if (c == p[0][0])
    add(r, '$');
  for (i = 0; i < n; i++) {
    for (j = 3; p[i][j]; j++) {
      if (p[i][j] == c) {
        if (p[i][j + 1]) {
          strcpy(t, "");
          FIRST(p[i][j + 1], t);
          for (k = 0; t[k]; k++)
            if (t[k] != 'e')
              add(r, t[k]);
          if (present(t, 'e') && p[i][0] != c) {
            strcpy(u, "");
            FOLLOW(p[i][0], u);
            for (k = 0; u[k]; k++)
              add(r, u[k]);
          }
        } else if (p[i][0] != c) {
          strcpy(u, "");
          FOLLOW(p[i][0], u);
          for (k = 0; u[k]; k++)
            add(r, u[k]);
        }
      }
    }
  }
}
int main(void) {
  int i, j;
  char c;
  printf("Enter number of productions: ");
  scanf("%d", &n);
  printf("Enter productions (use e for epsilon):\n");
  for (i = 0; i < n; i++)
    scanf("%19s", p[i]);
  printf("\nFIRST:\n");
  for (i = 0; i < n; i++) {
    c = p[i][0];
    if (!first[c - 'A'][0])
      FIRST(c, first[c - 'A']);
    if (i == 0 || p[i - 1][0] != c) {
      printf("FIRST(%c) = { ", c);
      for (j = 0; first[c - 'A'][j]; j++)
        printf("%c ", first[c - 'A'][j]);
      printf("}\n");
    }
  }
  printf("\nFOLLOW:\n");
  for (i = 0; i < n; i++) {
    c = p[i][0];
    if (!follow[c - 'A'][0])
      FOLLOW(c, follow[c - 'A']);
    if (i == 0 || p[i - 1][0] != c) {
      printf("FOLLOW(%c) = { ", c);
      for (j = 0; follow[c - 'A'][j]; j++)
        printf("%c ", follow[c - 'A'][j]);
      printf("}\n");
    }
  }
  return 0;
}
