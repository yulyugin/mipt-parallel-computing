#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    #pragma omp parallel private(i)
    {
        int i = omp_get_thread_num();
        printf("Before single section: %d\n", i);
        #pragma omp single copyprivate(i)
        {
            printf("Execute single section\n");
            i = 100500;
        }
        printf("After single section: %d\n", i);
    }

    return 0;
}
