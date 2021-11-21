#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include "scheduler.hpp"

using namespace std;

vector<double> ComputeStatistics(queue<task> finishedTaskArray){
    double waitTime = 0;
    double responseTime = 0;
    double turnaroundTime = 0;
    double totalCpuTime = 0;
    double cpuUsage = 0;
    int finishTime = 0;
    int tasks = finishedTaskArray.size();
    while(!finishedTaskArray.empty()) {
        turnaroundTime += finishedTaskArray.front().endTime - finishedTaskArray.front().arrivalTime;

        waitTime += finishedTaskArray.front().endTime - finishedTaskArray.front().arrivalTime - finishedTaskArray.front().cpuTime;

        totalCpuTime += finishedTaskArray.front().cpuTime;

        responseTime += finishedTaskArray.front().startTime - finishedTaskArray.front().arrivalTime;

        finishTime = max(finishTime, (int)finishedTaskArray.front().endTime);

        finishedTaskArray.pop();
    }
    vector<double> stats;

    stats.push_back(waitTime/tasks);
    stats.push_back(responseTime/tasks);
    stats.push_back(turnaroundTime/tasks);
    stats.push_back(totalCpuTime/(double)finishTime);


    return stats;
}