My project to detect memory leaks, and corrputions (underrun and overflow).
It's compatible with C and C++ applications.
It implements wrappers for C malloc/calloc/realloc/free and overloads for C++ new/delete operators.
It mantains a linked list with information about the memory blocks.

To use it in another project:
- include hh-main.h
- for C programs link with all src/*.c files
- for C++ programs link with all src/* files
- make the "include" dir visible to your program
- put DUMP_LEAKS and DUMP_CORRUPTIONS at the end of your main function like this

    int main() {
        ...
        DUMP_LEAKS
        DUMP_CORRUPTIONS
    }

Obs.: If you want to see a project using CMake please see other cpp projects in my profile