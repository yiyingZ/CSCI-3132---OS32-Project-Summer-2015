#include "OS32Memory.h"

#include <iostream>
#include <assert.h>

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
    if (size <= 0) {
        return nullptr;
    }

    // search for a block that is large enough for the header + block of memory
    size_t block_size = HEADER_SIZE + size;
    size_t real_aligned = wordAlign(size);
    size_t aligned = wordAlign(block_size);

    DEBUG_PRINT("allocate(%zu) :: aligned size = %zu\n", size, aligned);

    Block *best = this->findBlock(real_aligned, aligned);

    // no available block; attempt a sweep_merge to free one
    if (best == NULL) {
        DEBUG_PRINT("\t-> no best block; performing a sweep_merge!\n");
        this->performSweepMerge();
    }

    best = this->findBlock(real_aligned, aligned);

    // still no good block; no good
    if (best == nullptr) {
        DEBUG_PRINT("\t-> still could not find a good block; memory exhausted");
        return nullptr;
    }

    DEBUG_PRINT("\t-> Found best block @ %p with size %zu\n", best, best->size);

    // if the returned block exactly fits our request, then there's no need
    // to make a new block ... otherwise, it needs to be split
    if (real_aligned < best->size) {
        // create a new unallocated block after the found block
        size_t offset = block_size;

        Block *new_block = (best + offset);

        // new block init
        new_block->size = best->size - block_size;
        new_block->next = best->next; // best->x => best->new_block->x
        new_block->allocated = 0;

        DEBUG_PRINT("\t-> Creating unallocated block @ %p+%zu = %p with size %zu\n", best, offset, new_block, new_block->size);

        // allocated block fixup
        best->size = size;
        best->next = new_block;
    }

    best->allocated = 1;

    // zero out the allocated memory so that no information
    // leaks between memory requests
    void *allocatedBlock = (void *) (((intptr_t) best) + HEADER_SIZE);
    memset(allocatedBlock, 0, best->size);

    DEBUG_PRINT("\t-> Allocated requested block @ %p (blk: %p) with size %zu\n", allocatedBlock, best, best->size);

    this->debugPrint();

    return allocatedBlock;
}

void OS32Memory::free(void* mem) {
    if (mem == nullptr) {
        return;
    }

    Block *block = getBlockFromAddr(mem);

    if (block == nullptr) {
        DEBUG_PRINT("Invalid allocated memory @ %p\n", mem);
        return;
    }

    if (block->allocated == 0) {
        DEBUG_PRINT("Invalid release_memory request for %p (blk %p)! Memory block header does not exist.\n", mem, block);
        return;
    }

    DEBUG_PRINT("release_memory(%p) :: allocated size = %zu\n", block, block->size);

    // merge adjacent unallocated blocks
    while (block->next != nullptr && !block->next->allocated) {
        this->mergeBlockWithNext(block);
    }

    block->allocated = false;

    this->debugPrint();
}

size_t OS32Memory::getSize(void *mem) {
    if (mem == nullptr) {
        return 0;
    }

    Block *block = getBlockFromAddr(mem);

    if (block == nullptr || !block->allocated) {
        return 0;
    }

    return block->size;
}

void OS32Memory::performSweepMerge() {
    DEBUG_PRINT("Performing a sweep merge\n");

    Block *block = this->baseBlock;

    while (block != nullptr) {
        if (!block->allocated && block->next != NULL && !block->next->allocated) {
            this->mergeBlockWithNext(block);
        } else {
            // only advance the block when there are no more unallocated blocks found
            // in front of the current block
            block = block->next;
        }
    }

    this->debugPrint();
}

void OS32Memory::mergeBlockWithNext(Block *block) {
    assert(!block->allocated);
    assert(block->next != nullptr && !block->next->allocated);

    block->size += block->next->size + HEADER_SIZE;

    DEBUG_PRINT("\t-> merging with next block @ %p with size %zu; new size = %zu\n", block->next, block->next->size, block->size);

    block->next = block->next->next;
}

void OS32Memory::debugPrint() {
    #if DEBUG

    int allocated = 0;
    int free = 0;
    int overhead = 0;
    int blockNumber = 1;

    Block* block = this->baseBlock;

    while (block != NULL) {
        overhead += HEADER_SIZE;

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
