#include <cstdio>
#include <stdlib.h>

FILE* open(char *filename){
    printf("%s\n", filename);
    FILE *file;
    if (! (file = fopen(filename, "r"))) {
        printf("File %s can't be opened. Please retry ...\n", filename);
        return file;
    }
    printf("Open file: %s\n", filename);
    return file;
}
