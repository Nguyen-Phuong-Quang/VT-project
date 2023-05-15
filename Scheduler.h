#ifndef SCHEDULER

#define SCHEDULER

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "Task.h"

class Scheduler {
   public:
    void add_task(const Task& task);

    void run();

   private:
    std::vector<Task> tasks_;
};

#endif  // !SCHEDULER