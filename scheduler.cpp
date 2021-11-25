/*
 * COMP 3500
 * Rajesh Patel
 * Project 5
 * External Sources used are commented on corresponding line
 */

/* General imports */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <vector>
#include <math.h>

/* Project imports */
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

    /* Checks if number of arguments is correct */
    if (argc < 3 || argc > 4) {
        printf("Usage: command file_name [FCFS|RR [time_quantum]|SRTF]\n");
        return 0;
    }

    /* Handle the RR policy */
    int time_quantum = -1;
    if (strcmp(argv[2], "RR") == 0) {
        if (argc == 4){
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

    /* Checks if file is valid */
    fileName = argv[1];
    file = open(fileName);
    if(file == NULL) {
        printf("Invalid file\n");
        return EXIT_FAILURE;
    }

    /* Print file name */
    printf("The file name is %s\n", argv[1]);

    /* Print policy */
    if( !(strcmp(argv[2], "RR") == 0 || strcmp(argv[2], "FCFS") == 0 || strcmp(argv[2], "SRTF") == 0) ){
        printf("Invalid policy\n");
        return EXIT_FAILURE;
    }

    printf("The chosen policy is %s\n", argv[2]);

    /* Reads file */
    taskArray = readFile(file);

    /* If file is valid, size != 0 */
    if(taskArray.size() == 0){
        printf("Invalid file contents\n");
        return EXIT_FAILURE;
    }
 
    printf("There are %u tasks loaded from %s ...\n", (unsigned int)taskArray.size(), fileName);

    printf("Press any key to continue ...\n");
    getchar();
    fclose(file);

    /* Runs corresponding scheduling policy with file given */
    if(strcmp(argv[2], "RR") == 0){
        finishedTaskArray = RoundRobin(taskArray, time_quantum);
    } else if(strcmp(argv[2], "FCFS") == 0){
        finishedTaskArray = FirstComeFirstServe(taskArray);
    } else if(strcmp(argv[2], "SRTF") == 0){
        finishedTaskArray = ShortestJobRemainingFirst(taskArray);
    } else {
        printf("Usage: command file_name [FCFS|RR [time_quantum]|SRTF]\n");
        return 0;
    }

    /* Computes statistics that will be printed and stores them */
    vector<double> stats = ComputeStatistics(finishedTaskArray);

    /* Displays data */
    DisplayStatistics(stats);

    return EXIT_SUCCESS;
}