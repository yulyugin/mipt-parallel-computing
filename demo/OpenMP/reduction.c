#include <stdio.h>
#include <omp.h>

#define N 100

int main() {
    int i, a[N], sum;

    /* Initialize arithmetic progression. */
    for (i = 0; i < N; i++)
        a[i] = i;

    #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < N; i++)
            sum += a[i];

    printf("Arithmetic series: %d\n", sum);
    return 0;
}
