#include <stdio.h>
int n, m;
char alphabet[10];
int trans[10][10][10];
int dfa[20][10];
int dfa_count = 0;

int findstate(int state[]) {
  int i, j;
  for (i = 0; i < dfa_count; i++) {
    for (j = 1; j <= n; j++)
      if (dfa[i][j] != state[j])
        break;
    if (j > n)
      return i;
  }
  return -1;
}
void addstate(int state[]) {
  int i;
  if (findstate(state) == -1 && dfa_count < 20) {
    for (i = 1; i <= n; i++)
      dfa[dfa_count][i] = state[i];
    dfa_count++;
  }
}
void printstate(int state[]) {
  int i, empty = 1;
  printf("{");
  for (i = 1; i <= n; i++) {
    if (state[i]) {
      printf("q%d", i);
      empty = 0;
    }
  }
  if (empty)
    printf("NULL");
  printf("}");
}
int main(void) {
  int i, j, k, start, nofinal, notrans;
  int final[10], state[10] = {0}, newstate[10];
  int current, from, to;
  char symbol;
  printf("Enter number of alphabets: ");
  scanf("%d", &m);
  printf("Enter alphabets:\n");
  for (i = 0; i < m; i++)
    scanf(" %c", &alphabet[i]);
  printf("Enter number of states: ");
  scanf("%d", &n);
  printf("Enter start state: ");
  scanf("%d", &start);
  printf("Enter number of final states: ");
  scanf("%d", &nofinal);
  printf("Enter final states:\n");
  for (i = 0; i < nofinal; i++)
    scanf("%d", &final[i]);
  printf("Enter number of transitions: ");
  scanf("%d", &notrans);
  printf("Enter transitions:\n");
  for (i = 0; i < notrans; i++) {
    scanf("%d %c %d", &from, &symbol, &to);
    for (j = 0; j < m; j++)
      if (alphabet[j] == symbol)
        trans[from][j][to] = 1;
  }
  state[start] = 1;
  addstate(state);
  current = 0;
  while (current < dfa_count) {
    for (i = 0; i < m; i++) {
      for (j = 1; j <= n; j++)
        newstate[j] = 0;
      for (j = 1; j <= n; j++) {
        if (dfa[current][j]) {
          for (k = 1; k <= n; k++)
            if (trans[j][i][k])
              newstate[k] = 1;
        }
      }
      printf("\n");
      printstate(dfa[current]);
      printf(" --%c--> ", alphabet[i]);
      printstate(newstate);
      addstate(newstate);
    }
    current++;
  }
  printf("\n\nStates of DFA:\n");
  for (i = 0; i < dfa_count; i++) {
    printf("D%d = ", i);
    printstate(dfa[i]);
    for (j = 1; j <= n; j++) {
      if (dfa[i][j]) {
        for (k = 0; k < nofinal; k++) {
          if (j == final[k]) {
            printf(" (Final)");
            break;
          }
        }
        if (k < nofinal)
          break;
      }
    }
    printf("\n");
  }
  printf("\nStart state: ");
  printstate(dfa[0]);
  return 0;
}
