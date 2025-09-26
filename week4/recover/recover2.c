#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Accept a single command-line argument
  if (argc != 2) {

    printf("Usage: ./recover FILE\n");
    return 1;
  }

  // Open the memory card
  FILE *raw_file = fopen(argv[1], "r");

  if (raw_file == NULL) {

    printf("Error: Could not open %s\n", argv[1]);
    return 4;
  }

  // Create a buffer for a block of data
  uint8_t buffer[512];
  int jpg_count = 0;

  FILE *out = NULL;

  // While there's still data left to read from the memory card
  while (fread(buffer, 1, 512, raw_file) == 512) {

    // Create JPEGs from the data
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
        (buffer[3] & 0xF0) == 0xE0) {

      if (out) {
        fclose(out);
      }

      char filename[64];
      sprintf(filename, "%03d.jpg", ++jpg_count);

      out = fopen(filename, "w");
      fwrite(buffer, 1, 512, out);

    } else {

      if (out) {
        fwrite(buffer, 1, 512, out);
      }
    }
  }

  if (out)
    fclose(out);

  fclose(raw_file);

  return 0;
}
