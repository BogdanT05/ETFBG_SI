#include "Process.h"

Process::Process() : time_to_complete(0), maximum_waiting_time(0), waiting_time(0), execution_time(0){}

Process::Process(std::string name, int time_to_complete, int maximum_waiting_time, int waiting_time = 0,
                 int execution_time = 0) :
    name(std::move(name)),
    time_to_complete(time_to_complete),
    maximum_waiting_time(maximum_waiting_time),
    waiting_time(waiting_time),
    execution_time(execution_time)
{}

void Process::update_time_to_complete(int update) {
    time_to_complete = update;
}

void Process::update_maximum_waiting_time(int update) {
    maximum_waiting_time = update;
}

void Process::update_waiting_time(int update) {
    waiting_time += update;
}

void Process::update_execution_time(int update) {
    execution_time += update;
}

bool operator <(const Process& process1, const Process& process2) {
    if (process1.waiting_time != process2.waiting_time)
        return process1.waiting_time < process2.waiting_time;

    if (process1.execution_time != process2.execution_time)
        return process1.execution_time < process2.execution_time;

    return process1.name < process2.name;
}

bool operator>(const Process& process1, const Process& process2)
{
    return process2 < process1;
}