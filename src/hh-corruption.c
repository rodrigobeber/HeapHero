#include <memory.h>
#include "../include/hh-header.h"

int _isCorrupted(const unsigned char *guardLocation) {
    unsigned char guard[GUARD_SIZE];
    memset(guard, GUARD_FILL, GUARD_SIZE);
    return memcmp(guardLocation, guard, GUARD_SIZE);
}

int hhCorruptedBefore(struct hhMemoryBlockHeader *block) {
    return _isCorrupted((unsigned char *)&block->m_Guard);
}

int hhCorruptedAfter(struct hhMemoryBlockHeader *block) {
    unsigned char *pEnd = (unsigned char *)block + sizeof(struct hhMemoryBlockHeader) + block->m_Size;
    return _isCorrupted(pEnd);
}