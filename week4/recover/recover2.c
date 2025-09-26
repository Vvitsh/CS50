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

    // If the header is found in a block's first four bytes
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
        (buffer[3] & 0xF0) == 0xE0) {

      // Close the output file if it is in use
      if (out) {
        fclose(out);
      }

      // Create a filename and open our output file
      char filename[64];
      sprintf(filename, "%03d.jpg", ++jpg_count);
      out = fopen(filename, "w");

      // Handle the error if fopen fails
      if (!out) {
        printf("Error: Could not create %s\n", filename);
        fclose(raw_file);
        return 2;
      }
    }

    // If an output file is open, write the current bytes to file
    if (out) {
      fwrite(buffer, 1, 512, out);
    }
  }

  // Close out output file
  if (out)
    fclose(out);

  // Close out raw file
  fclose(raw_file);

  return 0;
}
