#include <stdio.h>
#include <stdint.h>

int main () {
    uint64_t rand = 0;
    uint32_t ecx = 0;
    uint32_t leaf = 1, subleaf = 0;

    // Check if RDRAND available in the CPU
    __asm__ __volatile__(
            "cpuid\n\t"
            :"=c"(ecx)
            :"a"(leaf), "c"(subleaf)
            :"ebx", "edx"
            );
    // CPUID.01H:ECX.RDRAND[bit 30]
    if (!(ecx && (1 << 30))) {
        fprintf(stderr, "RDRAND instruction unavailable");
        return 0;
    }

    __asm__ __volatile__(
            "rdrand %%rax\n\t"
            :"=a"(rand)
            ::
            );

    fprintf(stdout, "0x%llx\n", rand);
    return 0;
}
