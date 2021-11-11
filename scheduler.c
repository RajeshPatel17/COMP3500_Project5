/*
 * COMP 3500
 * Rajesh Patel
 * Project 5
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]){
    char *fileName;
    FILE *file;
    task taskArray[32];


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
        if (argc == 4)
            printf("time_quantum is set to %s\n", argv[3]);  
        else printf("Please enter time_quantum for the RR policy!\n");
    }

}