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

void reverseArray(int arr[], int len) {
  int start = 0;
  int end = len - 1;
  int tmp;

  while (start < end) {
    tmp = arr[start];
    arr[start] = arr[end];
    arr[end] = tmp;

    start++;
    end--;
  }
}

int main() {
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

  // NOTE: Part 1 - Extact, multiply, & sum the reverse of the first half of the
  // array
  int len = strlen(cc_str);
  int cc[len];
  int i;
  for (i = 0; i < len; i++) {
    cc[i] = cc_str[i] - '0';
  }

  printArrayDebug(cc, len);

  // Size the length of the array and then determine if odd or even to find
  // accurate halfway point
  int cc_len = sizeof(cc) / sizeof(cc[i]);
  int new_len;
  if (cc_len % 2 == 0) {
    new_len = cc_len / 2;
  } else {
    new_len = (cc_len + 1) / 2;
  }
  // BUG:
  // printf("%d\n", new_len);

  // Malloc is needed because we dont know the new size till compile time
  int *half_cc = (int *)malloc(new_len + sizeof(int));
  int j = 0;
  for (int i = 0; i < len; i += 2) {
    half_cc[j] = cc[i];
    j++;
  }

  // Reverse and multiply the digits by 2
  reverseArray(half_cc, new_len);
  printArrayDebug(half_cc, new_len);

  int digit_arr[new_len];
  for (int i = 0; i < new_len; i++) {
    digit_arr[i] = (half_cc[i] * 2);
  }
  printArrayDebug(digit_arr, new_len);

  // NOTE: WE ARE HERE
  // Sum the digits (Expected sum of 13 with test number)

  // NOTE: Remember to free up the malloc
  free(half_cc);
  return 0;
}

// Test number 4003600000000014

// int sum = 0;
// int tmp;
// for (int i = 0; i < new_len; i++) {
//   tmp = (half_cc[i] * 2);
//   sum += tmp;
//   tmp = 0;
// }

// printf("%d", sum);
