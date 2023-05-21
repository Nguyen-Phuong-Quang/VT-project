#ifndef TASK_H

#define TASK_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ucontext.h>
#include <memory>

#define STACK_SIZE 8192

class Task {
   public:
    Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size);

    // Static member function to serve as the entry point
    static void task_entry_point(Task* task);

    int get_id() const;
    int get_priority() const;
    int get_burst_time() const;
    ucontext_t* get_context();
    bool get_completed() const;
    void set_completed(bool completed);

   private:
    int id_;
    int priority_;
    int burst_time_;
    ucontext_t context_;
    std::vector<char> stack_;
    size_t stack_size_;
    void (*task_function_)(Task*);
    bool completed_ = false;
};



#endif // !TASK_H
