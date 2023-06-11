#include "Semaphore.h"

Semaphore::Semaphore(int count = 1) : count_(count) {}

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]() { return count_ > 0; });
    --count_;
}

void Semaphore::release() {
    std::lock_guard<std::mutex> lock(mutex_);
    ++count_;
    cv_.notify_one();
}
