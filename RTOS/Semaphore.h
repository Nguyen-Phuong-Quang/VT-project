#ifndef Semaphore_H

#define Semaphore_H
#include <mutex>
#include <condition_variable>

class Semaphore {
   public:
    Semaphore(int count);

    void acquire();

    void release();

   private:
    int count_;
    std::mutex mutex_;            // Mutex to synchronize access to shared resources
    std::condition_variable cv_;  
};


#endif  // !Semaphore_H
