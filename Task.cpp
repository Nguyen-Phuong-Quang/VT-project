#include "Task.h"

Task::Task(int id, int priority, int burst_time) : id_(id), priority_(priority), burst_time_(burst_time){}

int Task::get_id() const { return id_; }

int Task::get_priority() const { return priority_; }

int Task::get_burst_time() const { return burst_time_; }

bool Task::operator==(const Task& other) const {
    return id_ == other.id_;
}

void Task::execute() {
    std::cout << "Executing task " << id_ << " with priority " << priority_ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(burst_time_));
}