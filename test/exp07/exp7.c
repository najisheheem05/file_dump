#include <stdio.h>
int findvalue(char c) { return c - '0'; }
int main(void) {
  int noalpha, nostate, notrans;
  int eclos[10][20] = {0};
  int i, j, k, x, count, state, next, found;
  char alpha[5], trans[30][3];

  printf("Enter the number of alphabets?\n");
  scanf("%d", &noalpha);
  printf("NOTE:- [ use letter e as epsilon ]\n");
  printf("\nEnter alphabets?\n");
  for (i = 0; i < noalpha; i++)
    scanf(" %c", &alpha[i]);
  printf("\nEnter the number of states?\n");
  scanf("%d", &nostate);
  printf("\nEnter no of transition?\n");
  scanf("%d", &notrans);
  printf("\nEnter transition?\n");
  for (i = 0; i < notrans; i++) {
    scanf(" %c %c %c", &trans[i][0], &trans[i][1], &trans[i][2]);
  }

  printf("\ne-closure of states\n");
  for (i = 1; i <= nostate; i++) {
    count = 0;
    eclos[i][count++] = i;
    for (j = 0; j < count; j++) {
      state = eclos[i][j];
      for (k = 0; k < notrans; k++) {
        if (findvalue(trans[k][0]) == state && trans[k][1] == 'e') {
          next = findvalue(trans[k][2]);
          found = 0;
          for (x = 0; x < count; x++) {
            if (eclos[i][x] == next) {
              found = 1;
              break;
            }
          }
          if (!found && count < 20)
            eclos[i][count++] = next;
        }
      }
    }
  }
  for (i = 1; i <= nostate; i++) {
    printf("e-closure of q%d - {", i);
    for (j = 0; j < 20 && eclos[i][j] != 0; j++) {
      printf("q%d", eclos[i][j]);
      if (j + 1 < 20 && eclos[i][j + 1] != 0)
        printf(",");
    }
    printf("}\n");
  }
  return 0;
}
