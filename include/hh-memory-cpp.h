#ifndef _HH_MEMORY_CPP_H
#define _HH_MEMORY_CPP_H

#include <stddef.h>

void *operator new (size_t size, const char* pFunction, const char *pFile, int lineNo);
void *operator new[] (size_t size, const char* pFunction, const char *pFile, int lineNo);
void operator delete(void *p);
void operator delete[](void *p);

#endif /*_HH_MEMORY_CPP_H*/

