#ifndef KERNEL_H
#define KERNEL_H

#include <ucontext.h>
#include "Task.h"
#include "Scheduler.h"

class Kernel {
public:
    Kernel();

    void add_task(Task* task);

    ucontext_t* get_main_context();

    void run();

    void handle_time_slice();

private:
    Scheduler scheduler_;
    Task* current_task_ = nullptr;
    ucontext_t main_context_;
};

#endif // KERNEL_H
