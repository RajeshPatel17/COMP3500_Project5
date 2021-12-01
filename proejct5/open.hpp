#ifndef _OPEN_HPP
#define _OPEN_HPP

/* INFO: Function to test whether file specified exists and can be opened
 * 
 * ARGS: 
 *  char *filename: pointer to name of file to be opened
 * 
 * RETURN: 
 *  FILE*: pointer to file that was opened. NULL if file does not exist
 * 
 */
FILE* open(char *filename);

#endif