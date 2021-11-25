#ifndef _COMPUTE_HPP
#define _COMPUTE_HPP

/* INFO: Computes statistical analysis of finished tasks
 * 
 * ARGS: 
 *  queue<task>: a queue of finished tasks whose data will be processed
 * 
 * RETURN: 
 *  vector<double>: a vector holding information that will be returned
 * 
 */
std::vector<double> ComputeStatistics(std::queue<task> finishedTaskArray);

#endif