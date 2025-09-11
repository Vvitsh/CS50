#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkSpecialChars(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    char ch = str[i];
    if (!isalnum(ch)) {
      return 1;
    }
  }
  return 0;
}

void printArrayDebug(int arr[], int len) {
  printf("Interger array: ");
  for (int i = 0; i < len; i++) {
    printf("%d", arr[i]);
  }
  printf("\n");
}

int main(void) {
  string cc_str;
  int min = 13;
  int max = 16;

  while (1) {
    cc_str = get_string("Please enter a card number: ");
    if (cc_str != NULL) {
      if (checkSpecialChars(cc_str)) {
        printf("Error: Contains special characters - ");
      } else {
        if (strlen(cc_str) >= min && strlen(cc_str) <= max) {
          break;
        } else {
          printf("Error: Invalid character length - ");
        }
      }
    } else {
      printf("Error: Please try again - ");
    }
  }

  int len = strlen(cc_str);
  int cc[len];
  int i;
  for (i = 0; i < len; i++) {
    cc[i] = cc_str[i] - '0';
  }

  printArrayDebug(cc, len);
}
