#ifndef SCHEDULER_H

#define SCHEDULER_H

#include <iostream>
#include <chrono>
#include <vector>

#include "Task.h"

class Scheduler {
   public:
    void add_task(Task* task);
    Task* get_next_task();
    void chech_state();

   private:
    std::vector<Task*> tasks_;
};

#endif  // !SCHEDULER_H
