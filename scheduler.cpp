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

int main(int argc, char *argv[]){
    char *fileName;
    FILE *file;
    queue<task> taskArray;
    queue<task> finishedTaskArray;


    if (argc < 3 || argc > 4) {
        printf("Usage: command file_name [FCFS|RR|SRTF] [time_quantum]\n");
        return 0;
    }

    /* Print file name */
    printf("The file name is %s\n", argv[1]);

    /* Print policy */
    printf("The chosen policy is %s\n", argv[2]);

    /* Handle the RR policy */
    if (strcmp(argv[2], "RR") == 0) {
        if (argc == 4){
            int time_quantum = -1;
            sscanf(argv[3], "%d", &time_quantum);
            if(time_quantum<1){
                printf("Invalid time_quantum, please enter value of 1 or greater");
                return EXIT_FAILURE;
            }
            printf("time_quantum is set to %s\n", argv[3]);
        } else {
            printf("Please enter time_quantum for the RR policy!\n");
            return 0;
        }
    }

    fileName = argv[1];
    file = open(fileName);
    if(file == NULL) {
        printf("Invalid file\n");
        return EXIT_FAILURE;
    }

    taskArray = readFile(file);

    if(taskArray.size() == 0){
        printf("Invalid file contents\n");
        return EXIT_FAILURE;
    }
 
    printf("There are %u tasks loaded from %s ...\n", (unsigned int)taskArray.size(), fileName);

    printf("Press any key to continue ...\n");
    getchar();
    fclose(file);

    if(strcmp(argv[2], "RR") == 0){
        int time_quantum = -1;
        sscanf(argv[3], "%d", &time_quantum);
        if(time_quantum<1){
            printf("Invalid time_quantum, please enter value of 1 or greater");
            return EXIT_FAILURE;
        }
        finishedTaskArray = RoundRobin(taskArray, time_quantum);
    } else if(strcmp(argv[2], "FCFS") == 0){
        finishedTaskArray = FirstComeFirstServe(taskArray);
    } else if(strcmp(argv[2], "SRTF") == 0){
        finishedTaskArray = ShortestJobRemainingFirst(taskArray);
    } else {
        printf("Usage: command file_name [FCFS|RR|SRTF] [time_quantum]\n");
        return 0;
    }

    vector<double> stats = ComputeStatistics(finishedTaskArray);
    DisplayStatistics(stats);
    return EXIT_SUCCESS;
}