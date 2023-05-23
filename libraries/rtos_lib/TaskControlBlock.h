#ifndef TASKCONTROLBLOCK_H
#define TASKCONTROLBLOCK_H

#include <iostream>
#include <vector>
#include <ucontext.h>

struct TaskControlBlock {
    int id;
    int priority;
    int burst_time;
    std::vector<char> stack;
    size_t stack_size;
    ucontext_t context;
    // Add any additional properties you need for task control and management

    TaskControlBlock(int id, int priority, int burst_time, size_t stack_size);
};

#endif // TASKCONTROLBLOCK_H
