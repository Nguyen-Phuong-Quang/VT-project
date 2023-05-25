#include "Kernel.h"

Kernel::Kernel() {
    getcontext(&main_context_);
}

void Kernel::add_task(Task* task) {
    scheduler_.add_task(task);
}

ucontext_t* Kernel::get_main_context() { return &main_context_; }

void Kernel::run() {
    current_task_ = scheduler_.get_next_task();
    if(current_task_) {
        current_task_->set_task_state(TaskState::Running);
        swapcontext(&main_context_, current_task_->get_context());
    }

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        scheduler_.chech_state();
        if (current_task_->delay_time <= 0) {
            swapcontext(&main_context_, current_task_->get_context());
        }
    }
}

void Kernel::yield() {
    Task* next_task = scheduler_.get_next_task();

    if (next_task) {
        Task* current_task = current_task_;
        current_task->set_task_state(TaskState::Ready);
        next_task->set_task_state(TaskState::Running);
        current_task_ = next_task;
        swapcontext(current_task->get_context(), current_task_->get_context());
    }
}

void Kernel::delay(int times) {
    current_task_->set_task_state(TaskState::Suspended);
    current_task_->delay_time = times;
    swapcontext(current_task_->get_context(), &main_context_);
    current_task_->set_task_state(TaskState::Running);
}
