#ifndef TASK

#define TASK

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ucontext.h>
#include <memory>

#define STACK_SIZE 8192

class Task {
public:
    Task(int id, int priority, void (*task_function)(), int burst_time);

    ~Task();

    int get_id() const;
    int get_priority() const;
    int get_burst_time() const;
    ucontext_t* get_context();

private:
    int id_;
    int priority_;
    int burst_time_;
    ucontext_t context_;
    char* stack_;
    void (*task_function_)();
};



#endif // !DEMO
