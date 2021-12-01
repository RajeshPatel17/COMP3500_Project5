#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "scheduler.hpp"

using namespace std;

/* INFO: Function to print statistics that were found by ComputeStatistics in compute.cpp
 * 
 * ARGS: 
 *  vector<double>: Statistics to be printed. Must be in this order
 *  (1): average wait time
 *  (2): average response time
 *  (3): average turnaround time
 *  (4): total cpu usage
 * 
 * RETURN: 
 *  void
 * 
 */
void DisplayStatistics(vector<double> stats) {
    printf("\n");
    printf("average wait time: %.2f\n", stats.at(0));
    printf("average response time: %.2f\n", stats.at(1));
    printf("average turnaround time: %.2f\n", stats.at(2));
    printf("total cpu usage: %.2f % \n", stats.at(3)*100);
}