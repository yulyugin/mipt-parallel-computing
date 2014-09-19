#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 8;
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < N; i++)
            printf("%d: %d\n", id, i);
    }

    return 0;
}
