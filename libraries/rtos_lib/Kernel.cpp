#include "Kernel.h"
#include<vector>
#include<ucontext.h>

#define QUANTUM 1000 // microseconds

void task_default(Task* task) {
    while (1) {
    }
}

Task default_t(0, 0, task_default, 1000, STACK_SIZE);

Kernel::Kernel() {
    getcontext(&main_context_);
    default_t.set_task_state(TaskState::Running);
    scheduler_.add_task(&default_t);
}

void Kernel::add_task(Task* task) { scheduler_.add_task(task); }

ucontext_t* Kernel::get_main_context() { return &main_context_; }

void Kernel::run() {

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, nullptr);

    // Set the timer to interrupt every 1ms (1000 microseconds)
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = QUANTUM;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = QUANTUM;
    setitimer(ITIMER_REAL, &timer, nullptr);

    Task* next_task = scheduler_.get_next_task();

    if (next_task) {
        current_task_ = next_task;
        swapcontext(&main_context_, next_task->get_context());
    }
}

void Kernel::yield() {
    scheduler_.switch_task();
}

void Kernel::handle_time_slice() {
    std::vector<Task*> tasks = scheduler_.get_tasks();

    // Check task delay time and add task is running to running task of scheduler
    for (Task* task : tasks) {
        if (task->delay_time > 0) {
            task->delay_time--;
            if (task->delay_time == 0) {
                task->resume();  // Resume the task if delay is completed
            }
        }
    }

    Task* next_task = scheduler_.get_next_task();

    if (next_task) {
        Task* current_task = current_task_;
        current_task_ = next_task;
        swapcontext(current_task->get_context(), next_task->get_context());
    }
}

