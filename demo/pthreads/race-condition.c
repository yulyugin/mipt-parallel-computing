#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

const int N = 20000;
int x;

static void *thread_func(void *args) {
    int i;
    for(i = 0; i < N; ++i) {
        x++;
    }

    return NULL;
}

int main (int argc, char **argv) {
    int i;
    pthread_t thread;

    pthread_create(&thread, NULL, &thread_func, NULL);

    for(i = 0; i < N; i++) {
        if (x%2 == 0)
            printf("%d\n", x%2);
    }

    pthread_join(thread, NULL);

    exit(EXIT_SUCCESS);
}
