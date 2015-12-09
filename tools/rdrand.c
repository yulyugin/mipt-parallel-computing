#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main () {
    uint64_t random = 0;
    uint32_t ecx = 0;
    uint32_t leaf = 1, subleaf = 0;

    /* Check if RDRAND available in the CPU */
    __asm__ __volatile__(
            "cpuid\n\t"
            :"=c"(ecx)
            :"a"(leaf), "c"(subleaf)
            :"ebx", "edx"
            );

    if (!(ecx && (1 << 30))) { /* CPUID.01H:ECX.RDRAND[bit 30] */
        fprintf(stderr, "RDRAND instruction is unavailable."
                        " Using standart C rand() function.\n");
        srand(time(NULL)); /* Initialize random number generator */
        random = rand();
    } else {
        __asm__ __volatile__(
                "rdrand %%rax\n\t"
                :"=a"(random)
                ::
                );
    }

    fprintf(stdout, "0x%llx\n", random);
    return 0;
}
