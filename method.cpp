#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <vector>
#include "scheduler.hpp"

using namespace std;

queue<task> FirstComeFirstServe(queue<task> taskArray){

    unsigned int clock = 0;
    queue<task> readyQueue;
    queue<task> finishedTaskArray;
    while(!taskArray.empty() || !readyQueue.empty()){
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){
            readyQueue.push(taskArray.front());
            taskArray.pop();
        }
        if(!readyQueue.empty()){
            if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){
                readyQueue.front().startTime=clock;
            }
            readyQueue.front().remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.front().pid);
            if(readyQueue.front().remainingTime==0){
                readyQueue.front().endTime=clock+1;
                finishedTaskArray.push(readyQueue.front());
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.front().pid);
                readyQueue.pop();
                if(readyQueue.empty() && taskArray.empty()){
                    printf("<time %u> All processes finished...\n", clock);
                    return finishedTaskArray;
                } else if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){
                    readyQueue.front().startTime=clock;
                }
            }
        } else {
            printf("<time %u> No process is running\n", clock);
        }
        clock++;
    }
    return finishedTaskArray;
}

queue<task> RoundRobin(queue<task> taskArray, int time_quantum){
    int last_switch_clock = 0;
    unsigned int clock = 0;
    int rq = 0;
    vector<task> readyQueue;
    queue<task> finishedTaskArray;
    while(!taskArray.empty() || !readyQueue.empty()){
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){
            readyQueue.push_back(taskArray.front());
            taskArray.pop();
        }
        if(!readyQueue.empty()){
            if(last_switch_clock >= time_quantum){
                last_switch_clock = 0;
                rq++;
                if(rq >= readyQueue.size()){
                    rq = 0;
                }
            }
            if(readyQueue.at(rq).remainingTime == readyQueue.at(rq).cpuTime){
                readyQueue.at(rq).startTime = clock;
            }
            readyQueue.at(rq).remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.at(rq).pid);
            if(readyQueue.at(rq).remainingTime == 0){
                readyQueue.at(rq).endTime = clock+1;
                finishedTaskArray.push(readyQueue.at(rq));
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.at(rq).pid);
                readyQueue.erase(readyQueue.begin()+rq);
                if(rq >= readyQueue.size()){
                    rq = 0;
                }
                last_switch_clock = -1;
                if(readyQueue.empty() && taskArray.empty()){
                    printf("<time %u> All processes finished...\n", clock+1);
                    return finishedTaskArray;
                } else if(readyQueue.empty() && !taskArray.empty()){
                    continue;
                }else if(readyQueue.at(rq).remainingTime==readyQueue.at(rq).cpuTime){
                    readyQueue.at(rq).startTime=clock;
                } else if(readyQueue.at(rq).remainingTime == 0){
                    continue;
                }
            }
        } else {
            rq = 0;
            printf("<time %u> No process is running\n", clock);
        }
        clock++;
        last_switch_clock++;
    }
    return finishedTaskArray;
}

int shortestJobRemaining(vector<task> taskQueue){
    int shortestTimeRemaining = -1;
    int index = -1;
    int i = 0;
    while(i<taskQueue.size()) {
        if(taskQueue.at(i).remainingTime < shortestTimeRemaining){
            shortestTimeRemaining = taskQueue.at(i).remainingTime;
            index = i;
        }
        i++;
    }
    return index;
}

queue<task> ShortestJobRemainingFirst(queue<task> taskArray){

    unsigned int clock = 0;
    vector<task> readyQueue;
    queue<task> finishedTaskArray;
    int sjr;
    while(!taskArray.empty() || !readyQueue.empty()){
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){
            readyQueue.push_back(taskArray.front());
            taskArray.pop();
            sjr = shortestJobRemaining(readyQueue);
        }
        if(!readyQueue.empty()){
            if(readyQueue.at(sjr).remainingTime == readyQueue.at(sjr).cpuTime){
                readyQueue.at(sjr).startTime = clock;
            }
            readyQueue.at(sjr).remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.at(sjr).pid);
            if(readyQueue.at(sjr).remainingTime == 0){
                readyQueue.at(sjr).endTime = clock+1;
                finishedTaskArray.push(readyQueue.at(sjr));
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.at(sjr).pid);
                readyQueue.erase(readyQueue.begin()+sjr);
                sjr = shortestJobRemaining(readyQueue);
                if(sjr < 0 || readyQueue.at(sjr).remainingTime == 0){
                    continue;
                }
            }
        } else {
            printf("<time %u> No process is running\n", clock);
        }
        clock++;
    }
    return finishedTaskArray;
}