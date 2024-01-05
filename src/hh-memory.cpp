#include <stddef.h>
#include "../include/hh-memory-c.h"

void *operator new (size_t size, const char* pFunction, const char *pFile, int lineNo) {
    return hhMallock(size, pFunction, pFile, lineNo);
}

void *operator new[] (size_t size, const char* pFunction, const char *pFile, int lineNo) {
    return hhMallock(size, pFunction, pFile, lineNo);
}

void operator delete(void *p) {
    hhFree(p);
}

void operator delete[](void *p) {
    hhFree(p);
}
