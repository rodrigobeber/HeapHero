#ifndef  _HH_MEMORY_C_H
#define _HH_MEMORY_C_H

#include <stddef.h>
void *hhMallock(size_t size, const char* pFunction, const char *pFile, int lineNo);
void *hhCalloc(size_t num, size_t size, const char* pFunction, const char *pFile, int lineNo);
void *hhRealloc(void *p, size_t size, const char* pFunction, const char *pFile, int lineNo);
void hhFree(void *p);

#endif /*_HH_MEMORY_C_H*/