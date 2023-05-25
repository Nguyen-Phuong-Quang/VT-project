#include "Scheduler.h"
#include "Task.h"
#include "TaskState.h"

void Scheduler::add_task(Task* task) {
    tasks_.push_back(task);
}

Task* Scheduler::get_next_task() {
    if (tasks_.empty()) {
        return nullptr;
    }

    Task* next_task = nullptr;

    do {
        next_task = tasks_.front();
        tasks_.erase(tasks_.begin());
        tasks_.push_back(next_task);
    } while (next_task->get_task_state() != TaskState::Ready);

    return next_task;
}

void Scheduler::chech_state() {
    for (std::vector<Task*>::iterator task = tasks_.begin(); task < tasks_.end(); task++) {
        if ((*task)->get_task_state() == TaskState::Suspended) {
            (*task)->delay_time = (*task)->delay_time - 1;
        }
    }
}
