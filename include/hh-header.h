#ifndef _HH_HEADER_H
#define _HH_HEADER_H

#include <stddef.h>

#define GUARD_SIZE 4
#define GUARD_FILL 0XFD

struct hhMemoryBlockHeader {
    const char *m_pFunction; /* Holds the name of the function that allocates the memory */
    const char *m_pFile; /* Holds the source file name */
    struct hhMemoryBlockHeader *m_pPrev; /* Double linked list attribute */
    struct hhMemoryBlockHeader *m_pNext; /* Double linked list attribute */
    size_t m_Size; /* Size of the user memory */
    int m_LineNumber; /* The line number */
    int deletedButCorrupted; /* 1 - freed memory but there was a underrun or overflow, 0 - no conclusions to make */
    unsigned char m_Guard[GUARD_SIZE]; /* Guard before de user memory block */
};

#endif /*_HH_HEADER_H*/
