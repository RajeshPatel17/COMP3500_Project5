#ifndef _METHOD_HPP
#define _METHOD_HPP

std::queue<task> FirstComeFirstServe(std::queue<task> taskArray);

std::queue<task> RoundRobin(std::queue<task> taskArray, int time_quantum);

int shortestJobRemaining(std::vector<task> taskQueue);

std::queue<task> ShortestJobRemainingFirst(std::queue<task> taskArray);

#endif