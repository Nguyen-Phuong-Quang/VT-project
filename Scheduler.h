#ifndef SCHEDULER

#define SCHEDULER

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ucontext.h>
#include <memory>

#include "Task.h"

class Scheduler {
public:
    void add_task(Task* task);
    ucontext_t* get_context();
    Task* get_current_task();

    void run();

    void yield();

private:
    std::vector<Task*> tasks_;
    Task* current_task_ = nullptr;
    ucontext_t main_context_;
};

#endif  // !SCHEDULER
