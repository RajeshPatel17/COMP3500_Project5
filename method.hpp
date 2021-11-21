#ifndef _METHOD_HPP
#define _METHOD_HPP

queue<task> FirstComeFirstServe(queue<task> taskArray);

queue<task> RoundRobin(queue<task> taskArray, int time_quantum);

int shortestJobRemaining(vector<task> taskQueue);

queue<task> ShortestJobRemainingFirst(queue<task> taskArray);

#endif