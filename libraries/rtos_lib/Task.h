#ifndef TASK_H

#define TASK_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ucontext.h>
#include <memory>

#include "TaskControlBlock.h"

#define STACK_SIZE 8192

class Task {
   public:
    int delay_time = 0;

    Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size);

    // Static member function to serve as the entry point
    static void task_entry_point(Task* task);

    int get_id() const;
    int get_priority() const;
    int get_burst_time() const;
    TaskState get_task_state() const;
    void set_task_state(TaskState state) ;
    ucontext_t* get_context();

    void delay(int intervals);

   private:
    void (*task_function_)(Task*);
    TaskControlBlock tcb_;
};



#endif // !TASK_H
