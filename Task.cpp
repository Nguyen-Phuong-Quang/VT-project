#include "Task.h"


Task::Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size)
    : id_(id), priority_(priority), burst_time_(burst_time), stack_size_(stack_size) , task_function_(task_function){
    stack_.resize(stack_size_);
    getcontext(&context_);
    context_.uc_stack.ss_sp = stack_.data();
    context_.uc_stack.ss_size = stack_size;
    // Pass 'this' pointer as an argument to the static member function
    makecontext(&context_, (void (*)(void)) & Task::task_entry_point, 1, this);
}

// Static member function to serve as the entry point
void Task::task_entry_point(Task* task) {
    task->task_function_(task);  // Call the actual task function
}

int Task::get_id() const { return id_; }
int Task::get_priority() const { return priority_; }
int Task::get_burst_time() const { return burst_time_; }
ucontext_t* Task::get_context() { return &context_; }
bool Task::get_completed() const { return completed_; };
void Task::set_completed(bool completed) { completed_ = completed; };


