#include <cstring>
#include <climits>
#include "include/hh-main.h"

int main () {
    // Leak
    int *p = new int[5];

    // Corrupt
    char *p2 = (char*) malloc(6);
    strcpy(p2, "Hello world");
    delete p2;

    // Leak and corrupt
    char *p3 = new char[6];
    strcpy(p3, "Hello world");

    DUMP_LEAKS
    DUMP_CORRUPTIONS
}