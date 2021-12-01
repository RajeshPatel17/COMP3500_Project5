#ifndef _READ_HPP
#define _READ_HPP

/* INFO: Function to read file specified
 * 
 * ARGS: 
 *  FILE *file: pointer to file to be read
 * 
 * RETURN: 
 *  queue<task>: a queue of tasks that were read from file to be simulated
 * 
 */
std::queue<task> readFile(FILE *file);

#endif