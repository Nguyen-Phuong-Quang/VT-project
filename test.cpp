#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

#include "Task.h"
#include "Scheduler.h"

int main() {
    Task task1(1, 3, 2000);
    Task task2(2, 5, 1000);
    Task task3(3, 1, 500);

    Scheduler scheduler;
    scheduler.add_task(task1);
    scheduler.add_task(task2);
    scheduler.add_task(task3);

    scheduler.run();

    return 0;
}
