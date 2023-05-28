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

    Task* next_task = nullptr;

    while (1) {
        current_task_index = (current_task_index + 1) % tasks_.size();
        next_task = tasks_[current_task_index];

        if (next_task->get_task_state() == TaskState::Running)
            break;
    }
    return next_task;
}

void Scheduler::switch_task() {
    int size = tasks_.size();
    for (int i = 1; i < size; ++i) {
        if (tasks_[i]->get_task_state() == TaskState::Running) {
            tasks_[i]->set_task_state(TaskState::Ready);
            if (i + 1 < size) {
                tasks_[i + 1]->set_task_state(TaskState::Running);
            } else {
                tasks_[1]->set_task_state(TaskState::Running);
            }
            break;
        }
    }
}
