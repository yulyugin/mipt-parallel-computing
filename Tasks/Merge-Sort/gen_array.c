/**
 * Generates series of pceudo random integers in the following format:
 * a[0]
 * a[1]
 * ...
 * a[N]
 *
 * Author: Evgeny Yulyugin (yulyugin@gmail.com)
 * Year: 2014
 *
 * Arguments: N - size of generated array.
 * Result is printed in stdout.
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
  if(argc != 2) {
    printf("Invalid input format.\nUsage: %s [size of array]\n", argv[0]);
    return 1;
  }

  int i, n = atoi(argv[1]);

  for(i = 0; i < n; ++i)
    printf("%d\n", 1 + (int)(1000. * rand() / (RAND_MAX + 1.)));

  return 0;
}
