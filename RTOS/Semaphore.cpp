#include "Semaphore.h"

Semaphore::Semaphore(int count = 1) : count_(count) {}

void Semaphore::acquire() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]() { return count_ > 0; });
    --count_;
}

void Semaphore::release() {
    std::lock_guard<std::mutex> lock(mutex);
    ++count_;
    cv.notify_one();
}
