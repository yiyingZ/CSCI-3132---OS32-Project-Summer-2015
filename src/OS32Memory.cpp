#include "OS32Memory.h"

#include <iostream>

#define DEBUG 1
#define HEADER_SIZE (sizeof(Block))

#if DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__);
#else
#define DEBUG_PRINT(...)
#endif

/**
 * Aligns an address to the word boundary
 */
inline size_t wordAlign(size_t addr) {
    size_t mod = addr % MEMORY_WORD_SIZE;

    if (mod == 0) {
        // already word aligned
        return addr;
    } else {
        // round up to the next word
        return addr + MEMORY_WORD_SIZE - mod;
    }
}

OS32Memory::OS32Memory(size_t size) {
    void* block = std::malloc(size);

    if (block == NULL) {
        throw "Failed to initialize memory manager: malloc = NULL";
    }

    this->baseBlock = (Block*) block;
    this->baseBlock->size = size - HEADER_SIZE;
    this->baseBlock->next = nullptr;
    this->baseBlock->allocated = false;

    DEBUG_PRINT("Initialized memory with %ld bytes\n", size);
}

OS32Memory::~OS32Memory() {
    DEBUG_PRINT("Freeing memory\n");

    // Report leaked blocks in debug mode
    #if DEBUG
    this->performSweepMerge();
    this->debugPrint();

    // report any leaked blocks
    Block* block = this->baseBlock;

    do {
        if (block->allocated) {
            DEBUG_PRINT("Leaky block @ %p! %ld bytes were not freed back to the memory managed!\n", block, block->size);
        }

        block = block->next;
    } while (block != nullptr);
    #endif

    std::free(this->baseBlock);
    this->baseBlock = nullptr;
}

size_t OS32Memory::maxMemory() {
    DEBUG_PRINT("maxMemory is not implemented!\n");
    return 0;
}

size_t OS32Memory::usedMemory() {
    DEBUG_PRINT("usedMemory is not implemented!\n");
    return 0;
}

size_t OS32Memory::availMemory() {
    DEBUG_PRINT("availMemory is not implemented!\n");
    return 0;
}

size_t OS32Memory::totalUserMemory() {
    DEBUG_PRINT("totalUserMemory is not implemented!\n");
    return 0;
}

size_t OS32Memory::availUserMemory() {
    DEBUG_PRINT("availUserMemory is not implemented!\n");
    return 0;
}

void* OS32Memory::allocate(size_t size) {
    DEBUG_PRINT("allocate is not implemented!\n");
    return nullptr;
}

void OS32Memory::free(void* block) {
    DEBUG_PRINT("free is not implemented!\n");
}

void OS32Memory::performSweepMerge() {
    DEBUG_PRINT("performSweepMerge is not implemented!\n");
}

void OS32Memory::debugPrint() {
    #if DEBUG

    int allocated = 0;
    int free = 0;
    int overhead = 0;

    Block* block = this->baseBlock;

    while (block != NULL) {
        overhead += HEADER_SIZE;
        int blockNumber = 0;

        if (block->allocated == 1) {
            allocated += block->size;
        } else if (block->allocated == 0) {
            free += block->size;
        }

        printf("[block %d]\n", blockNumber);
        printf("\tpos: %p\n", block);
        printf("\tallocated: %s\n", block->allocated == 1 ? "yes" : "no");
        printf("\tsize: %zu\n", block->size);
        printf("\tnext: %p\n", block->next);

        block = block->next;
        blockNumber ++;
    }

    printf("Memory Usage\n");
    printf("\tBytes allocated: %d\n", allocated);
    printf("\tBytes free: %d\n", free);
    printf("\tBytes overhead: %d\n", overhead);

    #endif
}

Block* OS32Memory::findBlock(size_t realSize, size_t size) {
    Block* block = this->baseBlock;
    Block* best = nullptr;

    do {
        if (!block->allocated) {
            if (realSize == block->size) {
                // perfect size :-)
                return block;
            } else if (size <= block->size) {
                if (best != nullptr && block->size < best->size) {
                    // smaller than current best
                    best = block;
                } else if (best == nullptr) {
                    best = block;
                }
            }
        }

        block = block->next;
    } while (block != nullptr);

    return best;
}

Block* OS32Memory::getBlockFromAddr(void* mem) {
    Block* block = (Block*) (((intptr_t) mem) - HEADER_SIZE);

    // try to naively detect some invalid cases
    if (block->size == 0) {
        return nullptr;
    }

    return block;
}
