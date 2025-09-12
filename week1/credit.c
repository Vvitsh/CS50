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

void printArrayDebug(int arr[], int len, string label) {
  printf("Interger array %s: ", label);
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

int sumDigits(int arr[], int len) {
  int sum = 0;
  int tmp, digit;
  for (int i = 0; i < len; i++) {
    tmp = arr[i];
    while (tmp != 0) {
      digit = tmp % 10;
      sum += digit;
      tmp /= 10;
    }
  }
  return sum;
}

int main() {
  string cc_str;
  // Was getting warnings about the min/max length comparison, added
  // unsigned to shut the compiler up
  unsigned int min = 13;
  unsigned int max = 16;

  while (1) {
    cc_str = get_string("Please enter a card number: ");
    if (cc_str != NULL) {
      unsigned int len = strlen(cc_str);
      if (checkSpecialChars(cc_str)) {
        printf("Error: Contains special characters\n");
      } else {
        if (len >= min && len <= max) {
          break;
        } else {
          printf("Error: Invalid character length\n");
        }
      }
    } else {
      printf("Error: Please try again\n");
    }
  }

  // NOTE: Part 1 - Extact, multiply, & sum the reverse of every second element
  // of the original array
  int len = strlen(cc_str);
  int cc[len];
  for (int i = 0; i < len; i++) {
    cc[i] = cc_str[i] - '0';
  }

  // printArrayDebug(cc, len, "cc");

  // Size the length of the array and then determine if odd or even to find
  // accurate halfway point
  bool is_even_length;
  int cc_len = sizeof(cc) / sizeof(cc[0]);
  int new_len, odd_len;
  if (cc_len % 2 == 0) {
    new_len = cc_len / 2;
    is_even_length = true;
  } else {
    new_len = (cc_len + 1) / 2;
    is_even_length = false;
  }

  odd_len = new_len;

  if (is_even_length == false) {
    odd_len--;
  }
  // printf("%d\n", new_len);
  // printf("%d\n", odd_len);

  // Malloc is needed because we dont know the new size till compile time
  // TODO: Remember to free up the heap space from these malloc's
  int *first_half_cc = (int *)malloc(new_len * sizeof(int));
  int *second_half_cc = (int *)malloc(odd_len * sizeof(int));

  for (int i = 0, j = 0; i < len; i += 2, j++) {
    first_half_cc[j] = cc[i];
  }
  if (is_even_length == false) {
    for (int i = 1, j = 0; i < len - 1; i += 2, j++) {
      second_half_cc[j] = cc[i];
    }
  } else {
    for (int i = 1, j = 0; i < len; i += 2, j++) {
      second_half_cc[j] = cc[i];
    }
  }

  // printArrayDebug(first_half_cc, new_len, "first half cc");
  // printArrayDebug(second_half_cc, odd_len, "second half cc");

  // Reverse both array halfs
  reverseArray(first_half_cc, new_len);
  reverseArray(second_half_cc, odd_len);

  // multiply fist half
  int multiplied_digit_arr[new_len];
  for (int i = 0; i < new_len; i++) {
    multiplied_digit_arr[i] = (first_half_cc[i] * 2);
  }
  // printArrayDebug(digit_arr, new_len, "digit arr");

  // Sum the digits not the values (Expected sum of 13 with test number)
  int first_sum = sumDigits(multiplied_digit_arr, new_len);
  // printf("fist sum = %d\n", first_sum);

  // NOTE: Part 2 - Add the sum of the first half to the sum of the second half
  // of the digits not multiplied by 2
  int second_sum = sumDigits(second_half_cc, odd_len);
  // printf("second sum = %d\n", second_sum);

  int total_sum = first_sum + second_sum;
  // printf("total sum = %d\n", total_sum);

  // NOTE: Part 3 - If the total's modulo 10 is congruent to 0 the number is
  // valid
  // TODO: Final - Add logic to print the card type instead of VALID
  if (total_sum % 10 == 0) {
    // printf("VALID\n");
    int first_ele = cc[0];
    int second_ele = cc[1];
    int starting_digits = (first_ele * 10) + second_ele;

    if ((starting_digits == 34) || (starting_digits == 37)) {
      printf("AMEX\n");
    } else if ((starting_digits >= 51) && (starting_digits <= 55)) {
      printf("MASTERCARD\n");
    } else if (first_ele == 4) {
      printf("VISA\n");
    } else {
      printf("VALID\n");
    }
  } else {
    printf("INVALID\n");
  }

  // NOTE: free up the heap space used by the malloc's
  free(first_half_cc);
  free(second_half_cc);

  return 0;
}

// Test number 4003600000000014
