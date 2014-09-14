#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments.\nUsange: %s [number]\n",
                argv[0]);
        return 1;
    }

    int i, N = atoi(argv[1]);
    #pragma omp parallel if(N >= 8) private(i)
    {
        int id = omp_get_thread_num();
        for (i = 0; i < N; i++)
            printf("%d: %d\n", id, i);
    }

    return 0;
}
