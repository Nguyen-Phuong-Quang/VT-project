#include "Scheduler.h"
#include "Task.h"
#include "TaskState.h"

void Scheduler::add_task(Task* task) { tasks_.push_back(task); }

std::vector<Task*> Scheduler::get_tasks() {
    return tasks_;
}

Task* Scheduler::get_next_task() {
    if (tasks_.empty()) {
        return nullptr;
    }

    Task* next_task = tasks_.front();
    tasks_.erase(tasks_.begin());
    tasks_.push_back(next_task);

    return next_task;
}
