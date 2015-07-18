#include <string>

// the size of a word (in bytes). blocks of memory will be aligned to this word size
#define MEMORY_WORD_SIZE (4)

struct Block {

    /**
     * The size of the memory block
     */
    size_t size;

    /**
     * Pointer to the next block of memory
     */
    struct Block *next;

    /**
     * Flag for if the block is allocated or not
     */
    bool allocated;

};

#define MEMORY_HEADER_SIZE (sizeof(Block))

/**
 * Struct to store memory usage
 */
struct MemoryUsage {

    /**
     * The overhead byte count for kernel memory
     */
    size_t overhead;

    /**
     * Max kernel memory
     */
    size_t maxMemory;

    /**
     * Used kernel memory
     */
    size_t usedMemory;

    /**
     * Available kernel memory
     */
    size_t availableMemory;

};

/**
 * The OS32 memory manager. It manages memory allocations for both kernel and user memory.
 *
 * Note that the allocator is dynamic. Blocks of memory given out by the allocator have
 * some overhead which means that if the allocator is initialized with e.g. 1024 bytes
 * of memory, that full 1024 bytes of memory cannot be then allocated to something because
 * there will be overhead on that.
 *
 * As well, depending on how memory is allocated, there may be small regions of memory that
 * cannot be used for larger allocations. Consider the following hypothetical memory layout:
 *
 * |Used 1MB| |Free 1MB| |Used 5MB| |Free 2MB|
 *
 * If a caller wanted to receive a 1.5MB block of memory with the above current memory layout,
 * it would not be possible to give the request because there is nowhere to put it, even though
 * there is 3MB of free memory. Already allocated (used) blocks of memory cannot be moved.
 *
 * However, if one of the two used blocks were freed, the 1.5MB allocation would be immediately
 * possible because adjacent blocks could be merged into one larger block.
 */
class OS32Memory {

public:
    static OS32Memory& getInstance()
    {
        static OS32Memory instance;
        return instance;
    }

    /**
     * Deallocates all allocated memory.
     */
    ~OS32Memory();

    /**
     * Initializes the memory manager that allocates the given size number of bytes.
     *
     * If the memory manager is currently initialized, it will be reinitialized.
     *
     * @param kernelSize the bytes to allocate to kernel allocations
     * @param userSize the bytes to allocate to user allocation
     */
    void initialize(size_t kernelSize, size_t userSize);

    /**
     * Attempts to allocate a block of memory of the given size in kernel memory space.
     */
    void* kalloc(size_t size);

    /**
     * Frees the given block of kernel memory.
     */
    void kfree(void* mem);

    /**
     * Attempts to allocate a block of memory of the given size in user memory space.
     */
    void* alloc(size_t size);

    /**
     * Frees the given block of user memory.
     */
    void free(void* mem);

    /**
     * Gets the size of an allocated memory block.
     */
    size_t getSize(void* mem);

    /**
     * Returns the maximum amount of memory in bytes.
     */
    size_t maxMemory();

    /**
     * Returns the amount of memory used in bytes.
     */
    size_t usedMemory();

    /**
     * Returns the available amount of memory that can be allocated in bytes.
     */
    size_t availMemory();

    /**
     * Returns the amount of user memory in bytes.
     */
    size_t totalUserMemory();

    /**
     * Returns the amount of available user memory in bytes.
     */
    size_t availUserMemory();

    /**
     * Returns the memory usage of the kernel memory manager
     */
    MemoryUsage getKernelMemoryUsage();

    /**
     * Returns the memory usage of the user memory manager
     */
    MemoryUsage getUserMemoryUsage();

private:

    OS32Memory() { }

    /**
     * Memory is a singleton so these should be prevented
     */
    OS32Memory(OS32Memory const&) = delete;
    void operator=(OS32Memory const&) = delete;

    /**
     * The base block of kernel memory
     */
    Block* baseKernelBlock = nullptr;

    /**
     * The base block of user memory
     */
    Block* baseUserBlock = nullptr;

    /**
     * Debugging tool -- print all usage
     */
    void debugPrint();

    /**
     * Internal implementation of alloc
     */
    void* _alloc(Block* baseBlock, size_t size);

    /**
     * Internal implementation of free
     */
    void _free(void* mem);

    /**
     * Gets the header block for a given allocated block
     */
    Block* getBlockFromAddr(void *block);

    /**
     * Finds the best block to allocate into with the given size.
     *
     * @param baseBlock
     * @param realSize the real size of the block that is requested.
     * @param size the full size that should be requested (incl. header)
     */
    Block* findBlock(Block* baseBlock, size_t realSize, size_t size);

    /**
     * Merges the given block with the block after it. Both must be unallocated.
     */
    void mergeBlockWithNext(Block *block);

    /**
     * Perform a sweeping merge on any neighbouring unallocated blocks for the given base block.
     * free() already does merging when the next block is unallocated;
     * however it does not look at the previous block.
     * This is typically only used when a memory allocation is requested and
     * there are no free blocks to place it in; performSweepMerge() will attempt to
     * create a free block in the event of multiple adjacent unallocated blocks.
     */
    void performSweepMerge(Block* baseBlock);

};
