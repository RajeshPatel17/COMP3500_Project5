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

using namespace std;


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

queue<task> FirstComeFirstServe(queue<task> taskArray){

    unsigned int clock = 0;
    queue<task> readyQueue;
    queue<task> finishedTaskArray;
    task *runningTask = NULL;
    while(!taskArray.empty() || !readyQueue.empty()){
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){
            readyQueue.push(taskArray.front());
            taskArray.pop();
        }

        if(!readyQueue.empty()){
            if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){
                readyQueue.front().startTime=clock;
                //&runningTask = *readyQueue.front();
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
                    //*runningTask = readyQueue.front();
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

void RoundRobin(queue<task> taskArray, queue<task> finishedTaskArray){

}

void ShortestJobRemainingFirst(queue<task> taskArray, queue<task> finishedTaskArray){

}

void ComputeStatistics(queue<task> finishedTaskArray){

}

void DisplayStatistics(){

}


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

    fileName = argv[1];
    if (! (file = fopen(fileName, "r"))) {
        printf("File %s can't be opened. Please retry ...\n", fileName);
        return EXIT_FAILURE;
    }
    printf("Open file: %s\n", fileName);

    unsigned int count = 0;
    task *t = new task; //https://docs.microsoft.com/en-us/cpp/cpp/new-operator-cpp?view=msvc-170#:~:text=When%20new%20is%20used%20to%20allocate%20memory%20for,deallocate%20the%20memory%20allocated%20with%20the%20new%20operator.
    while (fscanf(file, "%u %u %u", &t->pid, &t->arrivalTime, &t->cpuTime)!= EOF) { // https://stackoverflow.com/questions/6547602/expression-must-have-class-type
        t->remainingTime = t->cpuTime;
        taskArray.push(*t);
        t = new task;
        count++;
    }
    /*while (fscanf(file, "%u %u %u", &taskArray[count].pid, &taskArray[count].arrivalTime, &taskArray[count].cpuTime)!= EOF) {
        count++;
    }*/
 
    printf("There are %u tasks loaded from %s ...\n", count, fileName);

    printf("Press any key to continue ...\n");
    getchar();
    fclose(file);

    if(strcmp(argv[2], "RR") == 0){
        RoundRobin(taskArray, finishedTaskArray);
    } else if(strcmp(argv[2], "FCFS") == 0){
        finishedTaskArray = FirstComeFirstServe(taskArray);
    } else if(strcmp(argv[2], "SRFT") == 0){
        ShortestJobRemainingFirst(taskArray, finishedTaskArray);
    } else {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum]\n");
        return 0;
    }

    return EXIT_SUCCESS;
}