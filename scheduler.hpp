#ifndef _SCHEDULER_HPP
#define _SCHEDULER_HPP

typedef struct task {
    unsigned int pid;
    unsigned int startTime;
    unsigned int endTime;
    unsigned int waitTime;
    unsigned int cpuTime;
    unsigned int arrivalTime;
    unsigned int responseTime;
    unsigned int remainingTime;
} task;

#endif 