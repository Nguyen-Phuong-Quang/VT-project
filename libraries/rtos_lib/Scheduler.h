#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "Task.h"

class Scheduler {
public:
    void add_task(Task* task);

    void add_runnning_task(Task* task);

    std::vector<Task*> get_tasks();

    Task* get_next_task();

    void filter_task();

    void switch_task();

private:
    std::vector<Task*> tasks_;
    std::vector<Task*> running_tasks_;
};

#endif  // !SCHEDULER_H
