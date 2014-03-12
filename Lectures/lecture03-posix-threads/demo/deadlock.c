#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

static void *thread_func(void *args) {
  usleep(100);
  pthread_mutex_lock(&A);
  usleep(100);
  pthread_mutex_lock(&B);
  usleep(100);
  pthread_mutex_unlock(&B);
  pthread_mutex_unlock(&A);

  return NULL;
}

int main (int argc, char **argv) {
  pthread_t thread;

  pthread_create(&thread, NULL, &thread_func, NULL);

  usleep(100);
  pthread_mutex_lock(&B);
  usleep(100);
  pthread_mutex_lock(&A);
  usleep(100);
  pthread_mutex_unlock(&A);
  pthread_mutex_unlock(&B);

  pthread_join(thread, NULL);

  printf("Success\n");

  pthread_mutex_destroy(&A);
  pthread_mutex_destroy(&B);

  exit(EXIT_SUCCESS);
}
