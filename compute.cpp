#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "scheduler.hpp"

using namespace std;

vector<double> ComputeStatistics(queue<task> finishedTaskArray){
    double waitTime = 0, responseTime = 0, turnaroundTime = 0, totalCpuTime = 0; //the sums of *variable name*
    int finishTime = 0;
    int tasks = finishedTaskArray.size(); // number of tasks
    while(!finishedTaskArray.empty()) {
        turnaroundTime += finishedTaskArray.front().endTime - finishedTaskArray.front().arrivalTime; //turnaround time = endTime - arrivalTime

        waitTime += finishedTaskArray.front().endTime - finishedTaskArray.front().arrivalTime - finishedTaskArray.front().cpuTime; //wait time = endTime - arrivalTime - cpuTime

        totalCpuTime += finishedTaskArray.front().cpuTime; //records cpu time to calculate cpu usage

        responseTime += finishedTaskArray.front().startTime - finishedTaskArray.front().arrivalTime; //response time = startTime - arrivalTime

        finishTime = max(finishTime, (int)finishedTaskArray.front().endTime); //finds when last process finished

        finishedTaskArray.pop();
    }
    vector<double> stats;

    stats.push_back(waitTime/tasks);
    stats.push_back(responseTime/tasks);
    stats.push_back(turnaroundTime/tasks);
    stats.push_back(totalCpuTime/(double)(finishTime)); //cpu usage. +1 is to account for first process starting at time = 0 rather than 1.

    return stats;
}