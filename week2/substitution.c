#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *key = argv[1];
  if (strlen(key) != 26) {
    printf("Key must contain 26 characters.");
  }
  printf("Key: %s", key);

  return 0;
}
