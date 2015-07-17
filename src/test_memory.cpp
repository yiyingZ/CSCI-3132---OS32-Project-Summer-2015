#include "OS32Memory.h"

#include <assert.h>

// expected size under 64 bit:
// 32 * (4 + 24) = 896
#define FIBO_MEM_SIZE (896)
#define FIBO_TABLE_SIZE (32)

/**
 * The purpose of this test is to test the very basics of the
 * memory allocator. It is basically just a dummy test to
 * ensure allocations will actually work.
 */
void test_fibo();

int main() {
    test_fibo();

    return 0;
}

/**
 * Compute the fibonacci series for a given n without a lookup table
 */
int fibo_compute(int n) {
    if (n == 0 || n == 1) {
        return n;
    } else {
        return fibo_compute(n - 1) + fibo_compute(n - 2);
    }
}

void test_fibo() {
    OS32Memory& memory = OS32Memory::getInstance();
    memory.initialize(FIBO_MEM_SIZE, FIBO_MEM_SIZE);

    int *fibo_table[FIBO_TABLE_SIZE];

    for (int i = 0; i < FIBO_TABLE_SIZE; i++) {
        fibo_table[i] = (int*) memory.alloc(sizeof(int));

        assert(memory.getSize(fibo_table[i]) == sizeof(int));

        *fibo_table[i] = fibo_compute(i);
    }

    for (int i = 0; i < FIBO_TABLE_SIZE; i++) {
        assert(*fibo_table[i] == fibo_compute(i));
    }

    for (int i = 0; i < FIBO_TABLE_SIZE; i++) {
        memory.free(fibo_table[i]);
    }
}