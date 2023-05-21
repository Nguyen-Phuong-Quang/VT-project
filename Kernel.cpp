#include "Kernel.h"
Kernel::Kernel() {
    getcontext(&main_context_);
}

void Kernel::add_task(Task* task) {
    scheduler_.add_task(task);
}

ucontext_t* Kernel::get_main_context() { return &main_context_; }

void Kernel::run() {
    while (true) {
        Task* next_task = scheduler_.get_next_task();

        if (next_task) {
            current_task_ = next_task;
            swapcontext(&main_context_, next_task->get_context());
        } else {
            break;
        }
    }
}

void Kernel::yield() {
    Task* current_task = current_task_;
    current_task_ = nullptr;
    swapcontext(current_task->get_context(), &main_context_);
}
