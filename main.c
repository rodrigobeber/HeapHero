#include<string.h>
#include "include/hh-main.h"


int main() {
    // Leak
    int *p = malloc(sizeof(int)*6);

    // Corrupt
    char *p2 = (char*) malloc(6);
    strcpy(p2, "Hello world");
    free(p2);

    // Leak and corrupt
    char *p3 = calloc(6, sizeof(char));
    strcpy(p3, "Hello world");

    DUMP_LEAKS
    DUMP_CORRUPTIONS
}