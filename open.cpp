#include <stdio.h>
#include <stdlib.h>

FILE open(char *filename){
    FILE *file;
    //fileName = argv[1];
    if (! (file = fopen(filename, "r"))) {
        printf("File %s can't be opened. Please retry ...\n", filename);
        return *file;
    }
    printf("Open file: %s\n", filename);
    return *file;
}
