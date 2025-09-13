#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  string cc_str;
  int len;

  while (1) {
    cc_str = get_string("Number: ");
    if (cc_str == NULL)
      continue;

    len = strlen(cc_str);
    int valid = 1;
    for (int i = 0; i < len; i++) {
      if (!isdigit(cc_str[i])) {
        valid = 0;
        break;
      }
    }

    if (!valid) {
      printf("Error: Must contain digits only\n");
    } else if (len < 13 || len > 16) {
      printf("Error: Invalid length\n");
    } else {
      break;
    }
  }

  int sum = 0;
  int alt = 0;

  for (int i = len - 1; i >= 0; i--) {
    int digit = cc_str[i] - '0';
    if (alt) {
      int doubled = digit * 2;
      sum += (doubled / 10) + (doubled % 10);
    } else {
      sum += digit;
    }
    alt = !alt;
  }

  if (sum % 10 == 0) {
    int first_digit = cc_str[0] - '0';
    int starting_digits = (first_digit * 10) + (cc_str[1] - '0');

    if (starting_digits == 34 || starting_digits == 37) {
      printf("AMEX\n");
    } else if ((starting_digits >= 51) && (starting_digits <= 55)) {
      printf("MASTERCARD\n");
    } else if (first_digit == 4) {
      printf("VISA\n");
    }
  } else {
    printf("INVALID\n");
  }
  return 0;
}
