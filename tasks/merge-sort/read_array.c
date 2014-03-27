/**
 * Reading an array form given file in the following format:
 * a[0]
 * a[1]
 * ...
 * a[N]
 *
 * Author: Evgeny Yulyugin (yulyugin@gmail.com)
 * Year: 2014
 *
 * Arguments: file name.
 */

#include <stdio.h>
#include <stdlib.h>

// Reading the array and measuring it's size
// Returning the size of the array
int read_array(char *filename, int **array) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("fopen");
    return -1;
  }
  char buf[256];
  int i, size = 0;

  while(fgets(buf, 256, file) != NULL)
    size++;

  if (fseek(file, 0L, SEEK_SET)) {
    perror("fseek");
    return -1;
  }

  *array = (int *)malloc(size * sizeof(int));
  if (*array == NULL) {
    perror("malloc");
    fclose(file);
    return -1;
  }

  for(i = 0; i < size; i++)
    fscanf(file, "%d", (*array) + i);

  fclose(file);
  return size;
}

int main (int argc, char **argv) {
  int *array, i;

  if(argc != 2) {
    printf("Invalid input format.\nUsage: %s [filename]\n", argv[0]);
    return 1;
  }

  // Reading the array
  int N = read_array(argv[1], &array);

  if (N < 0)
    return 1;

  printf("Array's size: %d\n", N);
  for (i = 0; i < N; ++i)
    printf("%d\n", array[i]);

  free(array);
  return 0;
}
