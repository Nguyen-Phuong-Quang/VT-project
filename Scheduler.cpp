#include "Scheduler.h"
#include "Task.h"


void Scheduler::add_task(Task* task) {
    tasks_.push_back(task);
}

Task* Scheduler::get_next_task() {
    if (tasks_.empty()) {
        return nullptr;
    }

    Task* next_task = nullptr;
    do {
        if (tasks_.empty()) {
            return nullptr;
        }
        next_task = tasks_.front();
        tasks_.erase(tasks_.begin());
    } while (next_task->get_completed());

    tasks_.push_back(next_task);
    return next_task;
}

