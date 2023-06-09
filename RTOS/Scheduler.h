#ifndef Scheduler_H

#define Scheduler_H

#include <vector>

#include "Task.h"

class Scheduler {
   public:
    void add_task(Task* task);

    std::vector<Task*> get_tasks();

    Task* get_next_task();

    void switch_task();

   private:
    std::vector<Task*> tasks_;
};

#endif  // !Scheduler_H
