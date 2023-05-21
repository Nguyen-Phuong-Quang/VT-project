#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Task.h"
#include "Kernel.h"
#define STACK_SIZE 8192

Kernel kernel;

void task1_handler(Task* task) {
    int count = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Task 1: " << count++ << std::endl;
        if (count == 2) {
            task->set_completed(true);
        }
        kernel.yield();
    }
}

void task2_handler(Task* task) {
    int count = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Task 2: " << count++ << std::endl;
        if (count == 3) {
            task->set_completed(true);
        }
        kernel.yield();
    }
}

void task3_handler(Task* task) {
    int count = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Task 3: " << count++ << std::endl;
        if (count == 4) {
            task->set_completed(true);
        }
        kernel.yield();
    }
}


int main(int argc, char *argv[])
{
    Task task1(1, 3, task1_handler, 1000, STACK_SIZE);
    Task task2(2, 2, task2_handler, 1000, STACK_SIZE);
    Task task3(3, 1, task3_handler, 1000, STACK_SIZE);

    kernel.add_task(&task1);
    kernel.add_task(&task2);
    kernel.add_task(&task3);

    getcontext(kernel.get_main_context());
    kernel.run();


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
