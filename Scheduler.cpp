#include "Scheduler.h"

void Scheduler::add_task(const Task& task) {
    tasks_.push_back(task);
}

void Scheduler::run() {
    while (!tasks_.empty()) {
        Task* next_task = nullptr;
        int highest_priority = -1;

        for (auto& task : tasks_) {
            if (task.get_priority() > highest_priority) {
                highest_priority = task.get_priority();
                next_task = &task;
            }
        }

        if (next_task) {
            next_task->execute();
            tasks_.erase(std::find(tasks_.begin(), tasks_.end(), *next_task));
        }
    }
}
