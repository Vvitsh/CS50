#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      double sum =
          image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;

      double avg = sum / 3.0;

      RGBTRIPLE grayscale_bm = {
          .rgbtBlue = avg, .rgbtGreen = avg, .rgbtRed = avg};

      image[i][j] = grayscale_bm;
    }
  }

  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {

  for (int i = 0; i < height; i++) {

    int start = 0;
    int end = width - 1;

    while (start < end) {

      RGBTRIPLE tmp = image[i][start];

      image[i][start] = image[i][end];
      image[i][end] = tmp;

      start++;
      end--;
    }
  }

  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {

  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  int set_len = sizeof(offsets) / sizeof(offsets[0]);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      int blue_channel = 0;
      int green_channel = 0;
      int red_channel = 0;
      int count = 0;

      for (int k = 0; k < set_len; k++) {

        int x = i + offsets[k][0];
        int y = j + offsets[k][1];

        if (x >= 0 && x < height && y >= 0 && y < width) {

          blue_channel += image[x][y].rgbtBlue;
          green_channel += image[x][y].rgbtGreen;
          red_channel += image[x][y].rgbtRed;

          count++;
        }
      }

      image[i][j].rgbtBlue = roundf((float)blue_channel / count);
      image[i][j].rgbtGreen = roundf((float)green_channel / count);
      image[i][j].rgbtRed = roundf((float)red_channel / count);
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) { return; }
