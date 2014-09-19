#include <stdio.h>
#include <omp.h>

int main() {
    int i, N = 100;
    #pragma parallel private(i)
    {
        int id = omp_get_thread_num();

        #pragma omp for ordered
        for (i = 0; i < N; i++) {
            printf("Thread %d, iteration %d\n", id, i);

            #pragma omp ordered
                printf("Thread %d, iteration %d\n", id, i);
        }
    }

    return 0;
}
