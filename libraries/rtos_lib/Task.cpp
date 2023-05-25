#include "Task.h"

Task::Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size)
    :  task_function_(task_function), tcb_(id, priority, burst_time, stack_size) {
    // Pass 'this' pointer as an argument to the static member function
    makecontext(&tcb_.context, (void (*)(void)) & Task::task_entry_point, 1, this);
}

// Static member function to serve as the entry point
void Task::task_entry_point(Task* task) {
    task->task_function_(task);  // Call the actual task function
}

int Task::get_id() const { return tcb_.id; }
int Task::get_priority() const { return tcb_.priority; }
int Task::get_burst_time() const { return tcb_.burst_time; }
TaskState Task::get_task_state() const { return tcb_.state; }
void Task::set_task_state(TaskState state) {
    tcb_.state = state;
}
ucontext_t* Task::get_context() { return &tcb_.context; }

void Task::delay(int intervals) {
    tcb_.state = TaskState::Suspended;
    delay_time = intervals;

    while (delay_time > 0) {
    }

    tcb_.state = TaskState::Ready;
}
