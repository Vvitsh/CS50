#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512

unsigned char *find_header(unsigned char *buffer, size_t buffer_len,
                           unsigned char *header, size_t header_len);

int main(int argc, char *argv[]) {

  if (argc < 2 || argc > 2) {
    printf("Usage: recover [image.jpg]\n");
    return 1;
  }

  char *input = argv[1];

  FILE *file = fopen(input, "rb");
  if (file == NULL) {
    printf("Error: Could not open %s\n", input);
    return 4;
  }

  unsigned char jpg_header[] = {0xFF, 0xd8, 0xFF}; // 0xe0 handle 4th byte?
  size_t header_len = sizeof(jpg_header);

  unsigned char *buffer = malloc(BLOCK_SIZE + header_len - 1);
  if (!buffer) {
    perror("Error: malloc failed\n");
    fclose(file);
    return 1;
  }

  size_t block_overlap = 0;
  long offset = 0;
  size_t bytes;

  while ((bytes = fread(buffer + block_overlap, 1, BLOCK_SIZE, file)) > 0) {
    size_t total = bytes + block_overlap;

    unsigned char *match = find_header(buffer, total, jpg_header, header_len);
  }

  free(buffer);
  fclose(file);

  return 0;
}

unsigned char *find_header(unsigned char *buffer, size_t buffer_len,
                           unsigned char *header, size_t header_len) {
  if (header_len == 0 || buffer_len < header_len)
    return NULL;

  for (size_t i = 0; i <= buffer_len - header_len; i++) {
    if (memcmp(buffer + i, header, header_len) == 0) {
      return buffer + i;
    }
  }

  return NULL;
}
