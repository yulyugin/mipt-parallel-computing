#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv) {
  double a[ISIZE][JSIZE];
  int i, j;
  FILE *ff;

  // Initialization
  for (i = 0; i < ISIZE; ++i) {
    for (j = 0; j < JSIZE; ++j) {
      a[i][j] = 10 * i + j;
    }
  }

  // Parallelize
  for (i = 1; i < ISIZE; ++i) {
    for (j = 0; j < JSIZE - 1; ++j) {
      a[i][j] = sin(0.00001 * a[i - 1][j + 1]);
    }
  }

  ff = fopen("2.out", "w");
  for (i = 0; i < ISIZE; ++i) {
    for (j = 0; j < JSIZE; ++j) {
      fprintf(ff, "%f ", a[i][j]);
    }
    fprintf(ff, "\n");
  }

  fclose(ff);
  return 0;
}
