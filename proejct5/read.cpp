/* References
 * 
 *  Line 24: I referenced this documentation to learn how to utilize the 'new' operator. 
 *  Line 25: I referenced this documentation as I was attempting to use the '.' operator to access "task" variables but learned I needed to use the arrow operator.
 */
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "scheduler.hpp"

using namespace std;

/* INFO: Function to read file specified
 * 
 * ARGS: 
 *  FILE *file: pointer to file to be read
 * 
 * RETURN: 
 *  queue<task>: a queue of tasks that were read from file to be simulated
 * 
 */
queue<task> readFile(FILE *file){
    queue<task> taskArray;
    task *t = new task; //https://docs.microsoft.com/en-us/cpp/cpp/new-operator-cpp?view=msvc-170#:~:text=When%20new%20is%20used%20to%20allocate%20memory%20for,deallocate%20the%20memory%20allocated%20with%20the%20new%20operator.
    while (fscanf(file, "%u %u %u", &t->pid, &t->arrivalTime, &t->cpuTime)!= EOF) { // https://stackoverflow.com/questions/6547602/expression-must-have-class-type
        t->remainingTime = t->cpuTime;
        taskArray.push(*t);
        t = new task;
    }
    return taskArray;
}