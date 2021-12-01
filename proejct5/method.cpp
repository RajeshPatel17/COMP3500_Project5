/* General Imports */
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <vector>

/* Project import for <task> */
#include "scheduler.hpp"

using namespace std;

/* INFO: First Come First Serve scheduling policy
 * 
 * ARGS: 
 *  queue<task>: a queue of tasks whos running process will be simulated
 * 
 * RETURN: 
 * queue<task>: a queue of tasks whose simulation is finished
 * 
 */
queue<task> FirstComeFirstServe(queue<task> taskArray){

    unsigned int clock = 0;
    queue<task> readyQueue;
    queue<task> finishedTaskArray;

    while(!taskArray.empty() || !readyQueue.empty()){

        /* adds tasks whose arrival time is after the current time */
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){

            readyQueue.push(taskArray.front());
            taskArray.pop();

        }

        /* if task queue is not empty runs task simulation  */
        if(!readyQueue.empty()){

            /* starts first task, (proper procedure in FCFS)*/
            if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){
                readyQueue.front().startTime=clock;
            }

            readyQueue.front().remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.front().pid);

            /* if current task is finished, then put task to rest */
            if(readyQueue.front().remainingTime==0){

                readyQueue.front().endTime=clock+1;
                finishedTaskArray.push(readyQueue.front());
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.front().pid);
                readyQueue.pop();
                
                /* if both queues are empty, then all tasks are finished and program finishes */
                if(readyQueue.empty() && taskArray.empty()){

                    printf("<time %u> All processes finished...\n", clock+1);
                    return finishedTaskArray;

                } else if( !readyQueue.empty() && readyQueue.front().remainingTime==readyQueue.front().cpuTime){ /* else initialize next process in queue if there is one*/

                    readyQueue.front().startTime=clock;

                }
            }
        } else {

            /* else no process is running */
            printf("<time %u> No process is running\n", clock);

        }

        clock++;
    }

    return finishedTaskArray;

}

/* INFO: Round Robin scheduling policy
 * 
 * ARGS: 
 *  queue<task>: a queue of tasks whos running process will be simulated
 *  int: maximum execution time of a process
 * 
 * RETURN: 
 *  queue<task>: a queue of tasks whose simulation is finished
 * 
 */
queue<task> RoundRobin(queue<task> taskArray, int time_quantum){

    int last_switch_clock = 0; /* how many TU ago a process switched */
    unsigned int clock = 0;
    queue<task> readyQueue;
    queue<task> finishedTaskArray;

    while(!taskArray.empty() || !readyQueue.empty()){

        /* adds tasks whose arrival time is after the current time */
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){

            readyQueue.push(taskArray.front());
            taskArray.pop();

        }

        /* if task vector is not empty runs task simulation  */
        if(!readyQueue.empty()){

            /* switches process if clock is greater equal to time quantum */
            if(last_switch_clock >= time_quantum){
                readyQueue.push(readyQueue.front());
                readyQueue.pop();
                last_switch_clock = 0;
            }

            /* starts at front which is in correspondence of Round Robin policy */
            if(readyQueue.front().remainingTime == readyQueue.front().cpuTime){
                readyQueue.front().startTime = clock;
            }

            readyQueue.front().remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.front().pid);

            /* if current task is finished, then put task to rest */
            if(readyQueue.front().remainingTime == 0){

                readyQueue.front().endTime = clock+1;
                finishedTaskArray.push(readyQueue.front());
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.front().pid);
                readyQueue.pop();

                /* resets last_switch_clock. -1 is for corner case. It gets corrected 
                 * since it will be incremented to 0 at the end of this if block.
                 */
                last_switch_clock = -1;

                /* if both queues are empty, then all tasks are finished and program finishes */
                if(readyQueue.empty() && taskArray.empty()){

                    printf("<time %u> All processes finished...\n", clock+1);
                    return finishedTaskArray;

                } else if(readyQueue.empty() && !taskArray.empty()){  /* restarts loop if arrived tasks are empty but not arrived tasks is not empty */
                    continue;
                }else if(readyQueue.front().remainingTime==readyQueue.front().cpuTime){ /* starts next task if available */
                    readyQueue.front().startTime=clock;
                } else if(readyQueue.front().remainingTime == 0){ /* corner case of next assumed task has remaining time of 0 but was not closed */
                    continue;
                }
            }
        } else {
            /* else last switch clock and no task is currently running */
            last_switch_clock = -1;
            printf("<time %u> No process is running\n", clock);
        }

        clock++;
        last_switch_clock++;

    }

    return finishedTaskArray;

}

/* INFO: Finds shortest job remaining
 * 
 * ARGS: 
 *  vector<task>: a vector of tasks who are currently being simulated
 * 
 * RETURN: 
 *  int: index of vector that has shortest time remaining
 * 
 */
int shortestJobRemaining(vector<task> taskQueue){

    int shortestTimeRemaining = -1;
    int index = -1;
    int i = 0;

    /* returns -1 if empty */
    if(taskQueue.empty()){
        return index;
    }

    /* loops through all tasks and keeps track of the shortest time remaining and index of said task */
    while(i<taskQueue.size()) { 
        if(taskQueue.at(i).remainingTime < shortestTimeRemaining){
            shortestTimeRemaining = taskQueue.at(i).remainingTime;
            index = i;
        }
        i++;
    }
    return index;
}

/* INFO: Shortest Remaining Task First scheduling policy
 * 
 * ARGS: 
 *  queue<task>: a queue of tasks whos running process will be simulated
 * 
 * RETURN: 
 *  queue<task>: a queue of tasks whose simulation is finished
 * 
 */
queue<task> ShortestJobRemainingFirst(queue<task> taskArray){

    unsigned int clock = 0;
    vector<task> readyQueue;
    queue<task> finishedTaskArray;
    int sjr; /* indexer for shortest remaining task */

    while(!taskArray.empty() || !readyQueue.empty()){

        /* adds tasks whose arrival time is after the current time */
        while(!taskArray.empty() && taskArray.front().arrivalTime <= clock){
            readyQueue.push_back(taskArray.front());
            taskArray.pop();
            /* finds shortest remaining task as each process is added
             * rather than every clock cycle for time complexity purposes 
             */
            sjr = shortestJobRemaining(readyQueue);
        }

        /* if task vector is not empty runs task simulation  */
        if(!readyQueue.empty()){
            
            /* starts process being pointed to, in accordance to SRTF policy */
            if(readyQueue.at(sjr).remainingTime == readyQueue.at(sjr).cpuTime){
                readyQueue.at(sjr).startTime = clock;
            }

            readyQueue.at(sjr).remainingTime--;
            printf("<time %u> process %u is running\n", clock, readyQueue.at(sjr).pid);

            /* if current task is finished, then put task to rest */
            if(readyQueue.at(sjr).remainingTime == 0){

                readyQueue.at(sjr).endTime = clock+1;
                finishedTaskArray.push(readyQueue.at(sjr));
                printf("<time %u> process %u is finished...\n", clock+1, readyQueue.at(sjr).pid);
                readyQueue.erase(readyQueue.begin()+sjr);

                /* finds new shortest task */
                sjr = shortestJobRemaining(readyQueue);

                /* if task doesnt exist or is corner case, then restart loop */
                if(sjr < 0 || readyQueue.at(sjr).remainingTime == 0){
                    continue;
                }
            }
        } else {
            /* else no process is currently running */
            printf("<time %u> No process is running\n", clock);
        }

        clock++;
    }

    return finishedTaskArray;
    
}