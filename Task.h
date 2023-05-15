#ifndef TASK

#define TASK

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

class Task {
public:
    Task(int id, int priority, int burst_time);

    int get_id() const;
    int get_priority() const;
    int get_burst_time() const;
    void execute();

    bool operator==(const Task& other) const;

private:
    int id_;
    int priority_;
    int burst_time_;
};



#endif // !DEMO
