#include "Scheduler.h"
void Scheduler::add_task(Task* task) { tasks_.push_back(task); }

std::vector<Task*> Scheduler::get_tasks() {
    return tasks_;
}

Task* Scheduler::get_next_task() {
    if (tasks_.empty()) {
        return nullptr;
    }

    Task* next_task = nullptr;
    int highest_priority = -1;

    for (Task* task : tasks_) {
        if (task->get_task_state() == TaskState::Running && task->get_priority() > highest_priority) {
            highest_priority = task->get_priority();
            next_task = task;
        }
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