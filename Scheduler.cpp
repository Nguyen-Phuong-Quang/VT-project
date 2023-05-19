#include "Scheduler.h"
#include "Task.h"

void Scheduler::add_task(Task* task) {
    tasks_.push_back(task);
}
ucontext_t* Scheduler::get_context() { return &main_context_; }
Task* Scheduler::get_current_task() {
    return current_task_;
}

void Scheduler::run() {
    while (!tasks_.empty()) {
        for (auto it = tasks_.begin(); it != tasks_.end();) {
            Task* next_task = *it;
            current_task_ = next_task;
            it = tasks_.erase(it);
            swapcontext(&main_context_, next_task->get_context());
            it = tasks_.insert(it, next_task);
            ++it;
        }
    }
}

void Scheduler::yield() {
    Task* current_task = current_task_;
    current_task_ = nullptr;
    swapcontext(current_task->get_context(), &main_context_);
}
