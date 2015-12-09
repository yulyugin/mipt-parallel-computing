#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int i, a[N];

    srand(time(NULL)); /* Initialize random number generator */

    for (i = 0; i < N; i++) /* Fill array with random numbers. */
        a[i] = rand();

    #pragma omp parallel for shared(a), schedule(dynamic)
        for (i = 0; i < N; i++)
            a[i] = a[i] * a[i];

    return 0;
}
