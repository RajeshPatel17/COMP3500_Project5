#ifndef _METHOD_HPP
#define _METHOD_HPP

/* INFO: First Come First Serve scheduling policy
 * 
 * ARGS: 
 *  queue<task>: a queue of tasks whos running process will be simulated
 * 
 * RETURN: 
 * queue<task>: a queue of tasks whose simulation is finished
 * 
 */
std::queue<task> FirstComeFirstServe(std::queue<task> taskArray);

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
std::queue<task> RoundRobin(std::queue<task> taskArray, int time_quantum);

/* INFO: Finds shortest job remaining
 * 
 * ARGS: 
 *  vector<task>: a vector of tasks who are currently being simulated
 * 
 * RETURN: 
 *  int: index of vector that has shortest time remaining
 * 
 */
int shortestJobRemaining(std::vector<task> taskQueue);

/* INFO: Shortest Remaining Task First scheduling policy
 * 
 * ARGS: 
 *  queue<task>: a queue of tasks whos running process will be simulated
 * 
 * RETURN: 
 *  queue<task>: a queue of tasks whose simulation is finished
 * 
 */
std::queue<task> ShortestJobRemainingFirst(std::queue<task> taskArray);

#endif