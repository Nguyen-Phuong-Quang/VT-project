#include "Task.h"

Task::Task(int id, int priority, void (*task_function)(), int burst_time) : id_(id), priority_(priority), task_function_(task_function), burst_time_(burst_time) {
    stack_ = new char[STACK_SIZE];
    getcontext(&context_);
    context_.uc_stack.ss_sp = stack_;
    context_.uc_stack.ss_size = STACK_SIZE;
    makecontext(&context_, task_function_, 0);
}

Task::~Task() {
    delete[] stack_;
}

int Task::get_id() const { return id_; }
int Task::get_priority() const { return priority_; }
int Task::get_burst_time() const { return burst_time_; }
ucontext_t* Task::get_context() { return &context_; }
