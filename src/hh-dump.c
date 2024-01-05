#include <stdio.h>
#include <string.h>
#include "../include/hh-header.h"
#include "../include/hh-corruption.h"

extern struct hhMemoryBlockHeader *pHead;

void _dumpBlock(const char* title, struct hhMemoryBlockHeader *block) {
    printf("\n%s\nBytes: %zu\nAddress: 0x%p\nFile: %s\nFunction: '%s', line number: %d\n",
           title,
           block->m_Size,
           (void *)(block+1),
           block->m_pFile,
           block->m_pFunction,
           block->m_LineNumber);
}

void hhDumpLeaks() {
    if (pHead == NULL) {
        return;
    }
    for (struct hhMemoryBlockHeader *p = pHead; p != NULL; p = p->m_pNext) {
        if (p->deletedButCorrupted == 0) {
            _dumpBlock("Memory leak", p);
        }
    }
}

void _dumpHeapCorruptionInfo(struct hhMemoryBlockHeader *block) {
    if (hhCorruptedBefore(block) != 0) {
        _dumpBlock("Heap corruption before memory block", block);
    }
    if (hhCorruptedAfter(block) != 0) {
        _dumpBlock("Heap corruption after memory block", block);
    }
}

void hhDumpCorruptions() {
    for (struct hhMemoryBlockHeader *p = pHead; p != NULL; p = p->m_pNext) {
        _dumpHeapCorruptionInfo(p);
    }
}