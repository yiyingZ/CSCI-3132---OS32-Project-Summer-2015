#include "OS32Memory.h"

#define TEST_MEM_SIZE (10 * 1024 * 1024)

int main() {
    std::unique_ptr<OS32Memory> memory(new OS32Memory(TEST_MEM_SIZE));

    return 0;
}
