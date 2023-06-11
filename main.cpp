#include <iostream>

#include "RTOS/index.h"

void print_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    std::cout << (now_tm->tm_year + 1900) << "/";                                   // Year
    std::cout << std::setfill('0') << std::setw(2) << (now_tm->tm_mon + 1) << "/";  // Month
    std::cout << std::setfill('0') << std::setw(2) << now_tm->tm_mday << " ";       // Day
    std::cout << std::setfill('0') << std::setw(2) << now_tm->tm_hour << ":";       // Hour
    std::cout << std::setfill('0') << std::setw(2) << now_tm->tm_min << ":";        // Minute
    std::cout << std::setfill('0') << std::setw(2) << now_tm->tm_sec << ":";        // Second

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::cout << std::setfill('0') << std::setw(3) << ms.count() % 1000 << " ";  // Milliseconds
}

Kernel kernel;
Semaphore semaphore(1);

void task1_handler(Task* task) {
    int count = 1;
    while (1) {
        task->delay(1000);

        semaphore.acquire();
        print_time();
        std::cout << "Task 1: " << count << std::endl;
        semaphore.release();

        if (count == 8) {
            kernel.yield();
        }
        count++;

        if (count > 10) count = 1;
    }
}

void task2_handler(Task* task) {
    int count = 20;
    while (1) {
        task->delay(500);

        semaphore.acquire();
        print_time();
        std::cout << "Task 2: " << count << std::endl;
        semaphore.release();

        if (count == 30) {
            kernel.yield();
        }
        count++;
        if (count > 40) count = 20;
    }
}

void task3_handler(Task* task) {
    int count = 100;
    while (1) {
        task->delay(250);

        semaphore.acquire();
        print_time();
        std::cout << "Task 3: " << count << std::endl;
        semaphore.release();

        if (count == 20) {
            kernel.yield();
        }
        count--;
        if (count < 0) count = 100;
    }
}



int main() {
    // Initial task with id, priority, function_handler, burst time, stack size
    Task task1(1, 3, task1_handler, 1000, STACK_SIZE);
    Task task2(2, 2, task2_handler, 1000, STACK_SIZE);
    Task task3(3, 3, task3_handler, 1000, STACK_SIZE);

    task1.set_task_state(TaskState::Running);
    // task2.set_task_state(TaskState::Running);
    // task3.set_task_state(TaskState::Running);
    kernel.add_task(&task1);
    kernel.add_task(&task2);
    kernel.add_task(&task3);

    getcontext(kernel.get_main_context());

    kernel.run();

    return 0;
}
