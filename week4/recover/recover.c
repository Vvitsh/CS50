#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc < 2 || argc > 2) {
    printf("Usage: recover [image.jpg]\n");
    return 1;
  }

  char *input_file = argv[1];

  FILE *fp = fopen(input_file, "r");
  if (fp == NULL) {
    printf("Could not open %s.\n", input_file);
    return 4;
  }

  char jpg_header[] = {0xFF, 0xd8, 0xFF}; // 0xe0 handle 4th byte?
  size_t header_len = sizeof(jpg_header);

  int bytes_read;
  char buffer[512];
  size_t buffer_len = sizeof(buffer);
  long offset = 0;

  while ((bytes_read = fread(buffer, 1, buffer_len, fp)) > 0) {
    for (int i = 0; i < bytes_read - header_len; ++i) {
      if (memcmp(&buffer[i], jpg_header, header_len) == 0) {
      }
    }
    offset += bytes_read;
  }

  fclose(fp);

  return 0;
}
