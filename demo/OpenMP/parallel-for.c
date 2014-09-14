#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 8;
    #pragma omp parallel for
    {
        int id = omp_get_thread_num();
        for (i = 0; i < N; i++)
            printf("%d: %d\n", id, i);
    }

    return 0;
}
