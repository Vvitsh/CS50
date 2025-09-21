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

  RGBTRIPLE copy[height][width];

  // Offset values compute the neighbours of each cell
  int offsets[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                       {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  int set_len = sizeof(offsets) / sizeof(offsets[0]);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      RGBTRIPLE blur_map;

      int count = 0;

      for (int k = 0; k < set_len; k++) {

        // Compute the neighbours relative to image[i][j]
        int x = i + offsets[k][0];
        int y = j + offsets[k][1];

        // Check the boundary of the cell for edges and corners
        if (x >= 0 && x < height && y >= 0 && y < width) {

          blur_map.rgbtBlue += image[x][y].rgbtBlue;
          blur_map.rgbtGreen += image[x][y].rgbtGreen;
          blur_map.rgbtRed += image[x][y].rgbtRed;

          count++;
        }
      }

      copy[i][j].rgbtBlue = roundf((float)blur_map.rgbtBlue / count);
      copy[i][j].rgbtGreen = roundf((float)blur_map.rgbtGreen / count);
      copy[i][j].rgbtRed = roundf((float)blur_map.rgbtRed / count);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      image[i][j] = copy[i][j];
    }
  }

  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {

  // Need to create a copy to record the sobel values
  RGBTRIPLE copy[height][width];

  int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      // Values to hold the gx/gy color channel sums
      int gxRed = 0, gxGreen = 0, gxBlue = 0;
      int gyRed = 0, gyGreen = 0, gyBlue = 0;

      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {

          // Calculate the kernel offsets for all neighbouring cells
          int x = i + dx;
          int y = j + dy;

          if (x >= 0 && x < height && y >= 0 && y < width) {

            // Calculate the color channel sums by multipling current color
            // channel by the gx/gy kernel value
            gxBlue += image[x][y].rgbtBlue * gx[dx + 1][dy + 1];
            gxGreen += image[x][y].rgbtGreen * gx[dx + 1][dy + 1];
            gxRed += image[x][y].rgbtRed * gx[dx + 1][dy + 1];

            gyBlue += image[x][y].rgbtBlue * gy[dx + 1][dy + 1];
            gyGreen += image[x][y].rgbtGreen * gy[dx + 1][dy + 1];
            gyRed += image[x][y].rgbtRed * gy[dx + 1][dy + 1];
          }
        }

        // Calculate the sobel filter by squaring the root of gx^2 + gy^2 and
        // clamp the value with fmin
        copy[i][j].rgbtBlue =
            fmin(255, round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2))));

        copy[i][j].rgbtGreen =
            fmin(255, round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2))));

        copy[i][j].rgbtRed =
            fmin(255, round(sqrt(pow(gxRed, 2) + pow(gyRed, 2))));
      }
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      image[i][j] = copy[i][j];
    }
  }

  return;
}
