#include <malloc.h>
#include <memory.h>
#include <stddef.h>
#include "../include/hh-header.h"
#include "../include/hh-corruption.h"

struct hhMemoryBlockHeader *pHead;

void _initializeBlockHeader(struct hhMemoryBlockHeader *block, size_t size, const char* function, const char *file, int lineNo) {
    block->m_Size = size;
    block->m_pFunction = function;
    block->m_pFile = file;
    block->m_LineNumber = lineNo;
    block->deletedButCorrupted = 0;
    block->m_pPrev = block->m_pNext = NULL;
}

void *hhMallock(size_t size, const char* pFunction, const char *pFile, int lineNo) {

    // Alloc block
    void *allocated_mem = malloc(sizeof(struct hhMemoryBlockHeader) + size + GUARD_SIZE);
    if (!allocated_mem) {
        return NULL;
    }

    // Block initialization
    struct hhMemoryBlockHeader *block = (struct hhMemoryBlockHeader*)allocated_mem;
    _initializeBlockHeader(block, size, pFunction, pFile,lineNo);

    // Guard areas
    unsigned char *pEnd = (unsigned char*)block + sizeof(struct hhMemoryBlockHeader) + size;
    memset(block->m_Guard, GUARD_FILL, GUARD_SIZE);
    memset(pEnd, GUARD_FILL, GUARD_SIZE);

    // List insertion
    if (!pHead) {
        pHead = block;
    } else {
        block->m_pNext = pHead;
        pHead->m_pPrev = block;
        pHead = block;
    }

    // Return pointer to user data
    return block + 1;
}

void *hhCalloc(size_t num, size_t size, const char* pFunction, const char *pFile, int lineNo) {
    // Calculate total allocation size
    size_t totalSize = num * size;

    // Use the hhMallock function to allocate and initialize memory
    void *allocated_mem = hhMallock(totalSize, pFunction, pFile, lineNo);
    if (!allocated_mem) {
        return NULL;
    }

    // Zero out the user memory block (calloc behavior)
    unsigned char *userMemStart = (unsigned char*)allocated_mem + sizeof(struct hhMemoryBlockHeader);
    memset(allocated_mem, 0, totalSize);

    return allocated_mem;
}

int _isValidBlock(struct hhMemoryBlockHeader *block) {
    for (struct hhMemoryBlockHeader *p = pHead; p != NULL; p = p->m_pNext) {
        if (block == p) {
            return 1;
        }
    }
    return 0;
}

void _removeBlock(struct hhMemoryBlockHeader *block) {
    // If corrupted keep it in the list marked as corrupted (but not leaked)
    if (hhCorruptedBefore(block) != 0 || hhCorruptedAfter(block) != 0) {
        block->deletedButCorrupted = 1;
        return;
    }
    // Remove
    if (block->m_pPrev != NULL) {
        block->m_pPrev->m_pNext = block->m_pNext;
    } else {
        pHead = block->m_pNext;
    }
    if (block->m_pNext != NULL) {
        block->m_pNext->m_pPrev = block->m_pPrev;
    }
    free (block);
}

void hhFree(void *p) {
    if (p == NULL) {
        return;
    }
    struct hhMemoryBlockHeader *block = (struct hhMemoryBlockHeader *)p;
    block -= 1;
    if (_isValidBlock(block)) {
        _removeBlock(block);
    }
}

void *hhRealloc(void *p, size_t size, const char* pFunction, const char *pFile, int lineNo) {

    // If the old pointer is NULL, then it's just like malloc
    if (p == NULL) {
        return hhMallock(size, pFunction, pFile, lineNo);
    }

    // If size is zero, free the memory and return NULL
    if (size == 0) {
        hhFree(p);
        return NULL;
    }

    // Adjust p to point to the start of the header
    struct hhMemoryBlockHeader *oldBlock = (struct hhMemoryBlockHeader*)p - 1;

    // Allocate new memory with the requested size
    void *new_mem = hhMallock(size, pFunction, pFile, lineNo);
    if (!new_mem) {
        return NULL;
    }

    // Calculate the size to be copied (the smaller of the old and new sizes)
    size_t oldSize = oldBlock->m_Size;
    size_t copySize = oldSize < size ? oldSize : size;

    // Copy the user data from the old memory block to the new one
    // Adjust new_mem to point to the user data part of the new block
    memcpy((unsigned char*)new_mem + sizeof(struct hhMemoryBlockHeader), (unsigned char*)p, copySize);

    // Free the old memory block
    hhFree(p);

    return new_mem;
}
