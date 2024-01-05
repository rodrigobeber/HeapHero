#ifndef _HH_MAIN_H
#define _HH_MAIN_H

#ifdef _DEBUG

    #include <stddef.h>

    #include "hh-memory-c.h"

    #define DUMP_LEAKS hhDumpLeaks();
    #define DUMP_CORRUPTIONS hhDumpCorruptions();
    void hhDumpLeaks();
    void hhDumpCorruptions();

    // c memory wrappers
    #define malloc(size) hhMallock(size, HH_FUNCTION_NAME, __FILE__, __LINE__)
    #define calloc(num, size) hhCalloc(num, size, HH_FUNCTION_NAME, __FILE__, __LINE__)
    #define realloc(ptr, size) hhRealloc(ptr, size, HH_FUNCTION_NAME, __FILE__, __LINE__)
    #define free hhFree

    // cross-platform for get function name
    #ifdef _WIN32
        #define HH_FUNCTION_NAME __FUNCSIG__
    #elif defined __GNUC__
        #define HH_FUNCTION_NAME __PRETTY_FUNCTION__
    #else
        #define HH_FUNCTION_NAME "Unkown function"
    #endif

    // cpp memory operator overload
    #ifdef __cplusplus
        #include "hh-memory-cpp.h"
        #define new new(__PRETTY_FUNCTION__, __FILE__, __LINE__) // Must be define here because can't be included by ptld_cpp.cpp
    #endif
#else
    // not in debug mode
    #include <malloc.h>
    #define DUMP_LEAKS
    #define DUMP_CORRUPTIONS
#endif



#endif /*_HH_MAIN_H*/