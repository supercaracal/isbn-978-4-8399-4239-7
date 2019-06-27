#include <stdlib.h>
#include <stdio.h>

#define M 4
#define N 5
#define MATRIX {\
    { 10, 11, 12, 13, 14 },\
    { 20, 21, 22,  0, 24 },\
    { 30,  0, 32, 33, 34 },\
    { 40, 41, 42, 43, 44 },\
  }

static void
print(int matrix[M][N]) {
  int i, j;

  for (i = 0; i < M; ++i) {
    for (j = 0; j < N; ++j) {
      fprintf(stdout, "%02d ", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

static void
fill_cross_zero(int matrix[M][N]) {
  int i, j;
  unsigned char columns;

  columns = 0;

  for (i = 0; i < M; ++i) {
    for (j = 0; j < N; ++j) {
      if (matrix[i][j] == 0) columns |= (1 << j);
    }
  }

  for (i = 0; i < M; ++i) {
    for (j = 0; j < N; ++j) {
      if (matrix[i][j] == 0) {
        for (j = 0; j < N; ++j) matrix[i][j] = 0;
        break;
      } else if ((columns >> j) & 1) {
        matrix[i][j] = 0;
      }
    }
  }
}

int
main(int argc, char **argv) {
  int matrix[M][N] = MATRIX;

  print(matrix);
  fprintf(stdout, "\n");
  fill_cross_zero(matrix);
  print(matrix);

  exit(0);
}
