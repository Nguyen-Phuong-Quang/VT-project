#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Task.h"
#include "Scheduler.h"

Scheduler scheduler;

void task1_handler() {
    Task* current_task = scheduler.get_current_task();
    int count = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(current_task->get_burst_time()));
        std::cout << "Task 1: " << count++ << std::endl;
        scheduler.yield();
    }
}

void task2_handler() {
    Task* current_task = scheduler.get_current_task();
    int count = 0;

    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(current_task->get_burst_time()));
        std::cout << "Task 2: " << count++ << std::endl;
        scheduler.yield();

    }
}

void task3_handler() {
    Task* current_task = scheduler.get_current_task();
    int count = 0;

    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(current_task->get_burst_time()));
        std::cout << "Task 3: " << count++ << std::endl;
        scheduler.yield();
    }
}


int main(int argc, char *argv[])
{
    Task task1(1, 3, task1_handler, 1000);
    Task task2(2, 2, task2_handler, 1000);
    Task task3(3, 1, task3_handler, 1000);

    scheduler.add_task(&task1);
    scheduler.add_task(&task2);
    scheduler.add_task(&task3);

    getcontext(scheduler.get_context());
    scheduler.run();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //    return app.exec();
}
