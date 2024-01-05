This my project to custom detect memory leaks, and corrputions (underrun and overflow)
It implements wrappers for C malloc/free and overloads for C++ new/delete operators.
It mantains a double linked this with all the allocated memory and informations.
It still needs some additional support like for realloc and calloc but the goal here is only skills demonstration.

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