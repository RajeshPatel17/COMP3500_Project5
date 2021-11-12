/*
 * COMP 3500
 * Rajesh Patel
 * Project 5
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

#define MAX_TASK_NUM 32

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

void FirstComeFirstServe(task *taskArray[], task *finishedTaskArray[]){
    unsigned int clock;
    task readyQueue[MAX_TASK_NUM];
    int rq = 0;
    int i;
    while(taskArray[i] != NULL){
        if(taskArray[i]->arrivalTime <= clock){
            task thisTask = *taskArray[i];
            taskArray[i] = NULL;
            readyQueue[rq] = thisTask;
            rq++;
        }
        vector<task> tasks;
    }
}

void RoundRobin(task *taskArray[], task *finishedTaskArray[]){

}

void ShortestJobRemainingFirst(task *taskArray[], task *finishedTaskArray[]){

}

double ComputeStatistics(task *finishedTaskArray[]){

}

void DisplayStatistics(){

}


int main(int argc, char *argv[]){
    char *fileName;
    FILE *file;
    task taskArray[MAX_TASK_NUM];
    task finishedTaskArray[MAX_TASK_NUM];


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
        printf("File %s can't be opened. Please retry ...\n");
        return EXIT_FAILURE;
    }
    printf("Open file: %s\n", fileName);

    int count = 0;

    while (fscanf(file, "%u %u %u", &taskArray[count].pid, &taskArray[count].arrivalTime, &taskArray[count].cpuTime)!= EOF) {
        count++;
    }
 
    printf("There are %u tasks loaded from %s ...\n", count, fileName);

    printf("Press any key to continue ...\n");
    getchar();
    fclose(file);

    if(strcmp(argv[2], "RR") == 0){
        RoundRobin(&taskArray, &finishedTaskArray);
    } else if(strcmp(argv[2], "FCFS") == 0){
        FirstComeFirstServe(&taskArray, &finishedTaskArray);
    } else if(strcmp(argv[2], "SRFT") == 0){
        ShortestJobRemainingFirst(&taskArray, &finishedTaskArray);
    } else {
        printf("Usage: command file_name [FCFS|RR|SRFT] [time_quantum]\n");
        return 0;
    }

    return EXIT_SUCCESS;
}