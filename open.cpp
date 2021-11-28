#include <cstdio>
#include <stdlib.h>

/* INFO: Function to test whether file specified exists and can be opened
 * 
 * ARGS: 
 *  char *filename: pointer to name of file to be opened
 * 
 * RETURN: 
 *  FILE*: pointer to file that was opened. NULL if file does not exist
 * 
 */
FILE* open(char *filename){
    FILE *file;
    if (! (file = fopen(filename, "r"))) {
        printf("File %s can't be opened...\n", filename);
        return file;
    }
    printf("Open file: %s\n", filename);
    return file;
}
