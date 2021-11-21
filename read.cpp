#include <stdio.h>
#include <queue>
#include "scheduler.hpp"

using namespace std;

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