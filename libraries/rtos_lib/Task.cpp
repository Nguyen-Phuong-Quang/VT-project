#include "Task.h"

Task::Task(int id, int priority, void (*task_function)(Task*), int burst_time, size_t stack_size)
    : task_function_(task_function), tcb_(id, priority, burst_time, stack_size) {
    makecontext(&tcb_.context, (void (*)(void)) & Task::task_entry_point, 1, this);
    old_state_ = tcb_.state;
}

void Task::task_entry_point(Task* task) {
    task->task_function_(task);
}

int Task::get_id() const { return tcb_.id; }
int Task::get_priority() const { return tcb_.priority; }
int Task::get_burst_time() const { return tcb_.burst_time; }
TaskState Task::get_task_state() const { return tcb_.state; }
void Task::set_task_state(TaskState state) { tcb_.state = state; }
ucontext_t* Task::get_context() { return &tcb_.context; }

void Task::delay(int intervals) {
    old_state_ = tcb_.state;
    tcb_.state = TaskState::Suspended;
    delay_time = intervals;
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() { return delay_time == 0; });
}

void Task::resume() {
    if (tcb_.state == TaskState::Suspended) {
        tcb_.state = old_state_;
        cv_.notify_all();
    }
}
