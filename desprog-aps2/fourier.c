#include <math.h>
#include "fourier.h"

void nft(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n, int sign)
{
  for (int k = 0; k < n; k++)
  {
    t[k] = 0;

    for (int j = 0; j < n; j++)
    {
      t[k] += s[j] * cexp(sign * 2 * PI * k * j * I / n);
    }
  }
}

void nft_forward(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n)
{
  nft(s, t, n, -1);
}

void nft_inverse(double complex t[MAX_SIZE], double complex s[MAX_SIZE], int n)
{
  nft(t, s, n, 1);

  for (int k = 0; k < n; k++)
  {
    s[k] /= n;
  }
}

void fft(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n, int sign)
{
  // t = frequency bins
  if (n == 1)
  {
    t[0] = s[0];
    return;
  }

  double complex se[n / 2];
  double complex te[n / 2];
  double complex so[n / 2];
  double complex to[n / 2];
  for (int i = 0; i < n; i += 2)
  {
    se[i / 2] = s[i];
    so[i / 2] = s[i + 1];
  }

  fft(se, te, n / 2, sign);
  fft(so, to, n / 2, sign);

  for (int m = 0; m < n / 2; m++)
  {
    t[m] = te[m] + to[m] * cexp(sign * 2 * PI * m * I / n);
    t[m + n / 2] = te[m] - to[m] * cexp(sign * 2 * PI * m * I / n);
  }
}

void fft_forward(double complex s[MAX_SIZE], double complex t[MAX_SIZE], int n)
{
  fft(s, t, n, -1);
}

void fft_inverse(double complex t[MAX_SIZE], double complex s[MAX_SIZE], int n)
{
  fft(t, s, n, 1);

  for (int k = 0; k < n; k++)
  {
    s[k] /= n;
  }
}

void fft_forward_2d(double complex matrix[MAX_SIZE][MAX_SIZE], int width, int height)
{
  double complex row[width];
  double complex col[height];
  double complex row_[width];
  double complex col_[height];

  // transformada de fourier das linhas
  for (int i = 0; i< height; i++) {
    for (int j = 0; j < width; j++) {
      row[j] = matrix[i][j];
    }
    fft_forward(row, row_, width);
    for (int k = 0; k < width; k++) {
      matrix[i][k] = row_[k];
    }
  }
  // transformada de fourier das colunas
  for (int j = 0; j < width; j++) {
    for (int i = 0; i < height; i++) {
      col[i] = matrix[i][j];
    }
    fft_forward(col, col_, height);
    for (int k = 0; k < height; k++) {
      matrix[k][j] = col_[k];
    }
  }
}

void fft_inverse_2d(double complex matrix[MAX_SIZE][MAX_SIZE], int width, int height)
{
  double complex row[width];
  double complex col[height];
  double complex row_[width];
  double complex col_[height];

  // transformada de fourier inversa das linhas
  for (int i = 0; i< height; i++) {
    for (int j = 0; j < width; j++) {
      row_[j] = matrix[i][j];
    }
    fft_inverse(row_, row, width);
    for (int k = 0; k < width; k++) {
      matrix[i][k] = row[k];
    }
  }
  // transformada de fourier inversa das colunas
  for (int j = 0; j < width; j++) {
    for (int i = 0; i < height; i++) {
      col_[i] = matrix[i][j];
    }
    fft_inverse(col_, col, height);
    for (int k = 0; k < height; k++) {
      matrix[k][j] = col[k];
    }
  }
}

void filter(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height, int flip)
{
  int center_x = width / 2;
  int center_y = height / 2;

  double variance = -2 * SIGMA * SIGMA;

  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      int dx = center_x - (x + center_x) % width;
      int dy = center_y - (y + center_y) % height;

      double d = dx * dx + dy * dy;

      double g = exp(d / variance);

      if (flip)
      {
        g = 1 - g;
      }

      output[y][x] = g * input[y][x];
    }
  }
}

void filter_lp(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height)
{
  filter(input, output, width, height, 0);
}

void filter_hp(double complex input[MAX_SIZE][MAX_SIZE], double complex output[MAX_SIZE][MAX_SIZE], int width, int height)
{
  filter(input, output, width, height, 1);
}
