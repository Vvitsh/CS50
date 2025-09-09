#include <stdio.h>
#include <string.h>

int main(void) {
  int val;
  int min = 1;
  int max = 8;

  while (1) {
    printf("Please provide a number between %d & %d: ", min, max);

    if (scanf("%d", &val) == 1) {
      if (val >= min && val <= max) {
        break;
      } else {
        printf("Error: Value out of range.\n");
      }
    } else {
      printf("Error: Invalid value.\n");
      while (getchar() != '\n')
        ;
    }
  }

  printf("\nYour number is %d\n\n", val);

  char stack[12] = "#";
  int count = val + 1;
  for (int i = 1; i <= val; i++) {
    printf("%*s  ", count, stack);
    printf("%-*s\n", count, stack);
    strcat(stack, "#");
  }

  return 0;
}
