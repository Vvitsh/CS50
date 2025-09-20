#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      double sum =
          image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
      double avg = sum / 3.0;

      RGBTRIPLE nuimage = {nuimage.rgbtBlue = avg, nuimage.rgbtGreen = avg,
                           nuimage.rgbtRed = avg};

      image[i][j] = nuimage;
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
void blur(int height, int width, RGBTRIPLE image[height][width]) { return; }

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) { return; }
