#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argv[1] == NULL) {
    printf("Key cannot be NULL.");
    return 1;
  }

  char *key = argv[1];
  char table[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  int key_len = strlen(key);
  if (key_len != 26) {
    printf("Key must contain 26 characters.");
    return 1;
  }

  string plaintext = get_string("plaintext: ");
  int str_len = strlen(plaintext);
  char ciphertext[str_len];

  for (int i = 0; i < key_len; i++) {
    char table_letter = tolower(table[i]);
    for (int j = 0; j < str_len; j++) {
      char str_letter = tolower(plaintext[j]);
      if (table_letter == str_letter) {
        ciphertext[j] = key[i];
      }
    }
  }
  printf("ciphertext: %s", ciphertext);

  return 0;
}
