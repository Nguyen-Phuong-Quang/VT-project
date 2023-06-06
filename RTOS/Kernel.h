#ifndef Kernel_H

#define Kernel_H

#include <signal.h>
#include <sys/time.h>
#include <ucontext.h>

#include <cstdint>
#include <iomanip>

#include "Scheduler.h"
#include "Task.h"
#include "constants.h"

class Kernel {
   public:
    struct sigaction sa;
    struct itimerval timer;

    Kernel();

    void add_task(Task* task);

    ucontext_t* get_main_context();

    void run();

    void yield();

    void handle_time_slice();

   private:
    Scheduler scheduler_;
    Task* current_task_ = nullptr;
    ucontext_t main_context_;
};

#endif  // !Kernel_H
