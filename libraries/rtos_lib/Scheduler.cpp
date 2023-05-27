#include "Scheduler.h"
#include "Task.h"
#include "TaskState.h"

void Scheduler::add_task(Task* task) { tasks_.push_back(task); }

void Scheduler::add_runnning_task(Task* task) {
    for (Task* t : running_tasks_) {
        if (t == task) {
            return;
        }
    }

    running_tasks_.push_back(task);
}

std::vector<Task*> Scheduler::get_tasks() {
    return tasks_;
}

Task* Scheduler::get_next_task() {
    if (running_tasks_.empty()) {
        return nullptr;
    }

    Task* next_task = running_tasks_.front();
    running_tasks_.erase(running_tasks_.begin());
    running_tasks_.push_back(next_task);
    return next_task;
}

void Scheduler::filter_task() {
    running_tasks_.erase(
                std::remove_if(
                    running_tasks_.begin(),
                    running_tasks_.end(),
                    [](Task* task) { return task->get_task_state() != TaskState::Running; }),
            running_tasks_.end());
}

void Scheduler::switch_task() {
    int size = tasks_.size();
    for (int i = 0; i < size; ++i) {
        if (tasks_[i]->get_task_state() == TaskState::Running) {
            tasks_[i]->set_task_state(TaskState::Ready);
            if (i + 1 < size) {
                tasks_[i + 1]->set_task_state(TaskState::Running);
            } else {
                tasks_[0]->set_task_state(TaskState::Running);
            }
            break;
        }
    }
}
