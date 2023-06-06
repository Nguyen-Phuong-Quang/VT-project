#include "TaskControlBlock.h"

TaskControlBlock::TaskControlBlock(int id, int priority, int burst_time, size_t stack_size)
    : id(id), priority(priority), burst_time(burst_time), stack_size(stack_size) {
    stack.resize(stack_size);
    getcontext(&context);

    context.uc_stack.ss_sp = stack.data();
    context.uc_stack.ss_size = stack_size;
    state = TaskState::Ready;
};