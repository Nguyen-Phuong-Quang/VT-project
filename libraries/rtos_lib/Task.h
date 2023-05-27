#ifndef TASK_H

#define TASK_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ucontext.h>
#include <memory>
#include <condition_variable>
#include <mutex>

#include "TaskControlBlock.h"

#define STACK_SIZE 8192

class Task {
   public:
    int delay_time;

    Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size);

    static void task_entry_point(Task* task);

    int get_id() const;
    int get_priority() const;
    int get_burst_time() const ;
    TaskState get_task_state() const ;
    void set_task_state(TaskState state) ;
    ucontext_t* get_context() ;

    void delay(int intervals) ;

    void resume() ;

   private:
    void (*task_function_)(Task*);
    TaskControlBlock tcb_;
    TaskState old_state_;
    std::mutex mutex_;
    std::condition_variable cv_;
};


#endif // !TASK_H
