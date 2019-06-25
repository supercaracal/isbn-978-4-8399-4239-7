#include <stdlib.h>
#include <stdio.h>

/*
#define N 2
#define MATRIX {\
    { 10, 11 },\
    { 20, 21 }\
  }
*/

/*
#define N 3
#define MATRIX {\
    { 10, 11, 12 },\
    { 20, 21, 22 },\
    { 30, 31, 32 }\
  }
*/

/*
#define N 4
#define MATRIX {\
    { 10, 11, 12, 13 },\
    { 20, 21, 22, 23 },\
    { 30, 31, 32, 33 },\
    { 40, 41, 42, 43 }\
  }
*/

#define N 5
#define MATRIX {\
    { 10, 11, 12, 13, 14 },\
    { 20, 21, 22, 23, 24 },\
    { 30, 31, 32, 33, 34 },\
    { 40, 41, 42, 43, 44 },\
    { 50, 51, 52, 53, 54 }\
  }

static void
print(int matrix[N][N]) {
  int i, j;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < N; ++j) {
      fprintf(stdout, "%d ", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }
}

static void
rotate(int matrix[N][N]) {
  int l, max_l, o, f, v, tmp;

  for (l = 0, max_l = N / 2; l < max_l; ++l) {
    for (o = l, f = N - 1 - l; o < f; ++o) {
      v = f - o + l;
      tmp = matrix[l][o];
      matrix[l][o] = matrix[v][l];
      matrix[v][l] = matrix[f][v];
      matrix[f][v] = matrix[o][f];
      matrix[o][f] = tmp;
    }
  }
}

int
main(int argc, char **argv) {
  int matrix[N][N] = MATRIX;

  print(matrix);
  fprintf(stdout, "\n");
  rotate(matrix);
  print(matrix);

  exit(0);
}
