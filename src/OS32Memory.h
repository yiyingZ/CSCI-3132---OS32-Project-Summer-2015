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

class OS32Memory {

public:

    /**
     * Creates a new memory instance that will allocate up to size bytes.
     */
    OS32Memory(size_t size);

    /**
     * Deallocates all allocated memory.
     */
    ~OS32Memory();

    /**
     * Updates the memory config
     * TODO ??
     */
    void updateMemConfig();

    /**
     * Attempts to allocate a block of memory of the given size and returns the block.
     */
    void* allocate(size_t size);

    /**
     * Frees the given block of memory.
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

private:

    /**
     * The base block of memory; i.e. the root.
     */
    Block* baseBlock;

    /**
     * Debugging tool -- print all usage
     */
    void debugPrint();

    /**
     * Gets the header block for a given allocated block
     */
    Block* getBlockFromAddr(void *block);

    /**
     * Finds the best block to allocate into with the given size.
     *
     * @param realSize the real size of the block that is requested.
     * @param size the full size that should be requested (incl. header)
     */
    Block* findBlock(size_t realSize, size_t size);

    /**
     * Merges the given block with the block after it. Both must be unallocated.
     */
    void mergeBlockWithNext(Block *block);

    /**
     * Perform a sweeping merge on any neighbouring unallocated blocks.
     * free() already does merging when the next block is unallocated;
     * however it does not look at the previous block.
     * This is typically only used when a memory allocation is requested and
     * there are no free blocks to place it in; performSweepMerge() will attempt to
     * create a free block in the event of multiple adjacent unallocated blocks.
     */
    void performSweepMerge();

};
