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

OS32Memory::~OS32Memory() {
    DEBUG_PRINT("Freeing memory\n");

    // Report leaked blocks in debug mode
    #if DEBUG
    this->performSweepMerge(baseKernelBlock);
    this->performSweepMerge(baseUserBlock);
    this->debugPrint();

    // report any leaked blocks
    Block* block = this->baseKernelBlock;

    do {
        if (block->allocated) {
            DEBUG_PRINT("Leaky kernel block @ %p! %ld bytes were not freed back to the memory managed!\n", block, block->size);
        }

        block = block->next;
    } while (block != nullptr);

    block = this->baseUserBlock;

    do {
        if (block->allocated) {
            DEBUG_PRINT("Leaky user block @ %p! %ld bytes were not freed back to the memory managed!\n", block, block->size);
        }

        block = block->next;
    } while (block != nullptr);
    #endif

    std::free(this->baseKernelBlock);
    std::free(this->baseUserBlock);
    this->baseKernelBlock = nullptr;
    this->baseUserBlock = nullptr;
}


void OS32Memory::initialize(size_t kernelSize, size_t userSize) {
    if (this->baseKernelBlock != nullptr) {
        std::free(this->baseKernelBlock);
        std::free(this->baseUserBlock);
        this->baseKernelBlock = nullptr;
        this->baseUserBlock = nullptr;
    }

    void* kernelBlock = std::malloc(kernelSize);

    if (kernelBlock == nullptr) {
        throw "Failed to initialize memory manager: malloc = NULL";
    }

    void* userBlock = std::malloc(userSize);

    if (userBlock == nullptr) {
        std::free(kernelBlock);
        throw "Failed to initialize memory manager: malloc = NULL";
    }

    this->baseKernelBlock = (Block*) kernelBlock;
    this->baseKernelBlock->size = kernelSize - HEADER_SIZE;
    this->baseKernelBlock->next = nullptr;
    this->baseKernelBlock->allocated = false;

    this->baseUserBlock = (Block*) userBlock;
    this->baseUserBlock->size = userSize - HEADER_SIZE;
    this->baseUserBlock->next = nullptr;
    this->baseUserBlock->allocated = false;

    DEBUG_PRINT("Initialized memory with %zu kernel bytes, %zu user bytes\n", kernelSize, userSize);
    this->debugPrint();
}

size_t OS32Memory::maxMemory() {
    return getKernelMemoryUsage().maxMemory;
}

size_t OS32Memory::usedMemory() {
    return getKernelMemoryUsage().usedMemory;
}

size_t OS32Memory::availMemory() {
    return getKernelMemoryUsage().availableMemory;
}

size_t OS32Memory::totalUserMemory() {
    return getUserMemoryUsage().maxMemory;
}

size_t OS32Memory::availUserMemory() {
    return getUserMemoryUsage().availableMemory;
}

MemoryUsage OS32Memory::getKernelMemoryUsage() {
    MemoryUsage usage { 0 };

    // Kernel memory
    Block* block = this->baseKernelBlock;

    while (block != NULL) {
        usage.overhead += HEADER_SIZE;
        usage.maxMemory += block->size + HEADER_SIZE;

        if (block->allocated) {
            usage.usedMemory += block->size;
        } else {
            usage.availableMemory += block->size;
        }

        block = block->next;
    }

    return usage;
}

MemoryUsage OS32Memory::getUserMemoryUsage() {
    MemoryUsage usage { 0 };

    // Kernel memory
    Block* block = this->baseUserBlock; // TODO

    while (block != NULL) {
        usage.overhead += HEADER_SIZE;
        usage.maxMemory += block->size + HEADER_SIZE;

        if (block->allocated) {
            usage.usedMemory += block->size;
        } else {
            usage.availableMemory += block->size;
        }

        block = block->next;
    }

    return usage;
}


void *OS32Memory::kalloc(size_t size) {
    return _alloc(baseKernelBlock, size);
}

void OS32Memory::kfree(void *mem) {
    _free(mem);
}

void *OS32Memory::alloc(size_t size) {
    return _alloc(baseUserBlock, size);
}

void OS32Memory::free(void *mem) {
    _free(mem);
}

void* OS32Memory::_alloc(Block *baseBlock, size_t size) {
    if (baseBlock == nullptr || size <= 0) {
        return nullptr;
    }

    // search for a block that is large enough for the header + block of memory
    size_t blockSize = HEADER_SIZE + size;
    size_t realAligned = wordAlign(size);
    size_t aligned = wordAlign(blockSize);

    DEBUG_PRINT("allocate(%zu) :: aligned size = %zu\n", size, aligned);

    Block *best = this->findBlock(baseBlock, realAligned, aligned);

    // no available block; attempt a sweep_merge to free one
    if (best == nullptr) {
        DEBUG_PRINT("\t-> no best block; performing a sweep_merge!\n");
        this->performSweepMerge(baseBlock);
    }

    best = this->findBlock(baseBlock, realAligned, aligned);

    // still no good block; no good
    if (best == nullptr) {
        DEBUG_PRINT("\t-> still could not find a good block; memory exhausted");
        return nullptr;
    }

    DEBUG_PRINT("\t-> Found best block @ %p with size %zu\n", best, best->size);

    // if the returned block exactly fits our request, then there's no need
    // to make a new block ... otherwise, it needs to be split
    if (realAligned < best->size) {
        // create a new unallocated block after the found block
        size_t offset = blockSize;

        Block *newBlock = (Block*) ((char*)best + offset);

        // new block init
        newBlock->size = best->size - blockSize;
        newBlock->next = best->next; // best->x => best->new_block->x
        newBlock->allocated = false;

        DEBUG_PRINT("\t-> Creating unallocated block @ %p+%zu = %p with size %zu\n", best, offset, newBlock, newBlock->size);

        // allocated block fixup
        best->size = size;
        best->next = newBlock;
    }

    best->allocated = true;

    // zero out the allocated memory so that no information
    // leaks between memory requests
    void *allocatedBlock = (void *) (((intptr_t) best) + HEADER_SIZE);
    memset(allocatedBlock, 0, best->size);

    DEBUG_PRINT("\t-> Allocated requested block @ %p (blk: %p) with size %zu\n", allocatedBlock, best, best->size);

    this->debugPrint();

    return allocatedBlock;
}

void OS32Memory::_free(void* mem) {
    if (mem == nullptr) {
        return;
    }

    Block *block = getBlockFromAddr(mem);

    if (block == nullptr) {
        DEBUG_PRINT("Invalid allocated memory @ %p\n", mem);
        return;
    }

    if (block->allocated == 0) {
        DEBUG_PRINT("Invalid free request for %p (blk %p)! Memory block header does not exist.\n", mem, block);
        return;
    }

    DEBUG_PRINT("free(%p) :: allocated size = %zu\n", block, block->size);

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

void OS32Memory::performSweepMerge(Block *baseBlock) {
    DEBUG_PRINT("Performing a sweep merge\n");

    Block *block = baseBlock;

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

    int blockNumber = 1;

    printf("Blocks [Kernel]\n");
    Block* block = baseKernelBlock;

    while (block != NULL) {
        printf("[Kernel block %d]\n", blockNumber);
        printf("\tpos: %p\n", block);
        printf("\tallocated: %s\n", block->allocated == 1 ? "yes" : "no");
        printf("\tsize: %zu\n", block->size);
        printf("\tnext: %p\n", block->next);

        block = block->next;
        blockNumber ++;
    }

    printf("Blocks [User]\n");
    block = baseKernelBlock;
    blockNumber = 1;

    while (block != NULL) {
        printf("[User block %d]\n", blockNumber);
        printf("\tpos: %p\n", block);
        printf("\tallocated: %s\n", block->allocated == 1 ? "yes" : "no");
        printf("\tsize: %zu\n", block->size);
        printf("\tnext: %p\n", block->next);

        block = block->next;
        blockNumber ++;
    }

    MemoryUsage usage = getKernelMemoryUsage();
    printf("Memory Usage [Kernel]\n");
    printf("\tManager size: %zu\n", usage.maxMemory);
    printf("\tBytes allocated: %zu\n", usage.usedMemory);
    printf("\tBytes free: %zu\n", usage.availableMemory);
    printf("\tBytes overhead: %zu\n", usage.overhead);

    usage = getUserMemoryUsage();
    printf("Memory Usage [User]\n");
    printf("\tManager size: %zu\n", usage.maxMemory);
    printf("\tBytes allocated: %zu\n", usage.usedMemory);
    printf("\tBytes free: %zu\n", usage.availableMemory);
    printf("\tBytes overhead: %zu\n", usage.overhead);

    #endif
}

Block* OS32Memory::findBlock(Block* baseBlock, size_t realSize, size_t size) {
    Block* block = baseBlock;
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
