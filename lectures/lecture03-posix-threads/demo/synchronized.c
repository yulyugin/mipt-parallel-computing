#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

const int N = 20000;
int x;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thread_func(void *args) {
  int i;
  for(i = 0; i < N; ++i) {
    pthread_mutex_lock(&mutex);
    x ++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}

int main (int argc, char **argv) {
  int i;
  pthread_t thread;

  pthread_create(&thread, NULL, &thread_func, NULL);

  for(i = 0; i < N; ++i) {
    pthread_mutex_lock(&mutex);
    if (x%2 == 0)
      printf("%d\n", x%2);
    pthread_mutex_unlock(&mutex);
  }

  pthread_join(thread, NULL);
  pthread_mutex_destroy(&mutex);

  exit(EXIT_SUCCESS);
}
