#include "OS32Memory.h"

#include <assert.h>

#define FIBO_TABLE_SIZE (32)
#define FIBO_MEM_SIZE (FIBO_TABLE_SIZE * (4 + MEMORY_HEADER_SIZE))

#define BIG_MEM_KERNEL_SIZE (1024 * 1024 * 10)
#define BIG_MEM_USER_SIZE (1024 * 1024 * 2)

/**
 * The purpose of this test is to test the very basics of the
 * memory allocator. It is basically just a dummy test to
 * ensure allocations will actually work.
 */
void test_fibo();

/**
 * The purpose of this test is to test big allocations and splitting
 * up big allocations into smaller blocks after freeing.
 */
void test_big_allocs();

int main() {
    test_fibo();
    test_big_allocs();

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

void test_big_allocs() {
    OS32Memory& memory = OS32Memory::getInstance();
    memory.initialize(BIG_MEM_KERNEL_SIZE, BIG_MEM_USER_SIZE);

    // Alloc |block 1| |big block 2| |block 3|
    void* block1 = memory.kalloc(1024 * 1024 * 2);
    void* block2 = memory.kalloc(1024 * 1024 * 6);
    void* block3 = memory.kalloc(1024 * 1024 * 1);

    assert(block1);
    assert(block2);
    assert(block3);

    // Split block2 into a 2 MB and 3 MB block
    memory.kfree(block2);
    void* block4 = memory.kalloc(1024 * 1024 * 2);
    void* block5 = memory.kalloc(1024 * 1024 * 3);

    assert(block4);
    assert(block5);

    memory.kfree(block1);
    memory.kfree(block3);
    memory.kfree(block4);
    memory.kfree(block5);
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