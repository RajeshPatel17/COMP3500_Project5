/*
 * COMP 3500
 * Rajesh Patel
 * Project 5
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>


#include "scheduler.hpp"
#include "read.hpp"
#include "open.hpp"
#include "print.hpp"
#include "compute.hpp"
#include "method.hpp"

using namespace std;


/*typedef struct task {
    unsigned int pid;
    unsigned int startTime;
    unsigned int endTime;
    unsigned int waitTime;
    unsigned int cpuTime;
    unsigned int arrivalTime;
    unsigned int responseTime;
    unsigned int remainingTime;
} task;*/

/*queue<task> FirstComeFirstServe(queue<task> taskArray){

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
            if(readyQueue.front().remainingTime==0){
                readyQueue.front().endTime=clock;
                finishedTaskArray.push(readyQueue.front());
                printf("<time %u> process %u is finished...\n", clock, readyQueue.front().pid);
                readyQueue.pop();
                if(readyQueue.empty() && taskArray.empty()){
                    printf("<time %u> All processes finished...\n", clock);
                    return finishedTaskArray;
                } else if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){
                    readyQueue.front().startTime=clock;
                }
            }
            readyQueue.front().remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.front().pid);
        } else {
            printf("<time %u> No process is running\n", clock);
        }
        clock++;
    }
    return finishedTaskArray;
}

queue<task> RoundRobin(queue<task> taskArray, int time_quantum){
    unsigned int last_switch_clock = 0;
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
            if(clock - last_switch_clock == time_quantum){
                last_switch_clock = clock;
                rq++;
                if(rq >= readyQueue.size()){
                    rq = 0;
                }
            }
            if(readyQueue.at(rq).remainingTime == readyQueue.at(rq).cpuTime){
                readyQueue.at(rq).startTime = clock;
            }
            if(readyQueue.at(rq).remainingTime == 0){
                readyQueue.at(rq).endTime = clock;
                finishedTaskArray.push(readyQueue.at(rq));
                printf("<time %u> process %u is finished...\n", clock, readyQueue.at(rq).pid);
                readyQueue.erase(readyQueue.begin()+rq);
                if(rq >= readyQueue.size()){
                    rq = 0;
                }
                last_switch_clock = clock;
                if(readyQueue.empty() && taskArray.empty()){
                    printf("<time %u> All processes finished...\n", clock);
                    return finishedTaskArray;
                } else if(readyQueue.empty() && !taskArray.empty()){
                    continue;
                }else if(readyQueue.at(rq).remainingTime==readyQueue.at(rq).cpuTime){
                    readyQueue.at(rq).startTime=clock;
                } else if(readyQueue.at(rq).remainingTime == 0){
                    continue;
                }
            }
            readyQueue.at(rq).remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.at(rq).pid);
        } else {
            rq = 0;
            printf("<time %u> No process is running\n", clock);
        }
        clock++;

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
            if(readyQueue.at(sjr).remainingTime == 0){
                readyQueue.at(sjr).endTime = clock;
                finishedTaskArray.push(readyQueue.at(sjr));
                printf("<time %u> process %u is finished...\n", clock, readyQueue.at(sjr).pid);
                readyQueue.erase(readyQueue.begin()+sjr);
                sjr = shortestJobRemaining(readyQueue);
                if(sjr < 0 || readyQueue.at(sjr).remainingTime == 0){
                    continue;
                }
            }
            readyQueue.at(sjr).remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.at(sjr).pid);
        } else {
            printf("<time %u> No process is running\n", clock);
        }
        clock++;
    }
    return finishedTaskArray;
}

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

void DisplayStatistics(vector<double> stats) {

}*/


int main(int argc, char *argv[]){
    char *fileName;
    FILE *file;
    queue<task> taskArray;
    queue<task> finishedTaskArray;


    if (argc < 2 || argc > 4) {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum]\n");
        return 0;
    }

    /* Print file name */
    printf("The file name is %s\n", argv[1]);

    /* Print policy */
    printf("The chosen policy is %s\n", argv[2]);

    /* Handle the RR policy */
    if (strcmp(argv[2], "RR") == 0) {
        if (argc == 4){
            printf("time_quantum is set to %s\n", argv[3]);
        } else {
            printf("Please enter time_quantum for the RR policy!\n");
            return 0;
        }
    }

    /* = argv[1];
    if (! (file = fopen(fileName, "r"))) {
        printf("File %s can't be opened. Please retry ...\n", fileName);
        return EXIT_FAILURE;
    }
    printf("Open file: %s\n", fileName);*/
    file = open(fileName);

    taskArray = readFile(file);

    /*unsigned int count = 0;
    task *t = new task; //https://docs.microsoft.com/en-us/cpp/cpp/new-operator-cpp?view=msvc-170#:~:text=When%20new%20is%20used%20to%20allocate%20memory%20for,deallocate%20the%20memory%20allocated%20with%20the%20new%20operator.
    while (fscanf(file, "%u %u %u", &t->pid, &t->arrivalTime, &t->cpuTime)!= EOF) { // https://stackoverflow.com/questions/6547602/expression-must-have-class-type
        t->remainingTime = t->cpuTime;
        taskArray.push(*t);
        t = new task;
        count++;
    }*/
    /*while (fscanf(file, "%u %u %u", &taskArray[count].pid, &taskArray[count].arrivalTime, &taskArray[count].cpuTime)!= EOF) {
        count++;
    }*/
 
    printf("There are %u tasks loaded from %s ...\n", (unsigned int)taskArray.size(), fileName);

    printf("Press any key to continue ...\n");
    getchar();
    fclose(file);

    if(strcmp(argv[2], "RR") == 0){
        int time_quantum = -1;
        sscanf(argv[3], "%d", &time_quantum);
        if(time_quantum<1){
            printf("Invalid time_quantum, please enter value of 1 or greater");
        }
        finishedTaskArray = RoundRobin(taskArray, time_quantum);
    } else if(strcmp(argv[2], "FCFS") == 0){
        finishedTaskArray = FirstComeFirstServe(taskArray);
    } else if(strcmp(argv[2], "SRFT") == 0){
        finishedTaskArray = ShortestJobRemainingFirst(taskArray);
    } else {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum]\n");
        return 0;
    }

    vector<double> stats = ComputeStatistics(finishedTaskArray);
    DisplayStatistics(stats);
    return EXIT_SUCCESS;
}