#ifndef SCHEDULER_H

#define SCHEDULER_H

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

    Task* get_next_task();

   private:
    std::vector<Task*> tasks_;
};

#endif  // !SCHEDULER_H
