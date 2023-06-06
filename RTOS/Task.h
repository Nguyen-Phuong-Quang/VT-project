#ifndef TASK_H

#define TASK_H

#include <ucontext.h>

#include <condition_variable>
#include <mutex>

#include "constants.h"
#include "TaskControlBlock.h"
#include "TaskState.h"

class Task {
   public:
    Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size);

    static void task_entry_point(Task* task);
    int get_id() const;
    int get_priority() const;
    int get_burst_time() const;
    TaskState get_task_state() const;
    void set_task_state(TaskState state);
    ucontext_t* get_context();

    void delay(int interval);

    void resume();

    int get_delay_time();

    void decrease_delay_time();

   private:
    TaskControlBlock tcb_;
    void (*task_function_)(Task*);
    int delay_time;
    TaskState old_state_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
#endif  // !TASK_H
