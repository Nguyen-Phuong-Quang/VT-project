#ifndef TaskControlBlock_H

#define TaskControlBlock_H

#include <ucontext.h>

#include <vector>

#include "TaskState.h"

struct TaskControlBlock {
    int id;
    int priority;
    int burst_time;
    std::vector<char> stack;
    size_t stack_size;
    ucontext_t context;
    TaskState state;

    TaskControlBlock(int id, int priority, int burst_time, size_t stack_size);
};

#endif // !TaskControlBlock_H