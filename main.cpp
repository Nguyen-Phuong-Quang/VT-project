#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "libraries/rtos_lib/RTOS.h"
#define STACK_SIZE 8192

void print_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm* now_tm = std::localtime(&now_c);

    std::cout << (now_tm->tm_year + 1900) << ":";  // Năm
    std::cout << (now_tm->tm_mon + 1) << ":";      // Tháng
    std::cout << now_tm->tm_mday << " ";           // Ngày
    std::cout << now_tm->tm_hour << ":";           // Giờ
    std::cout << now_tm->tm_min << ":";            // Phút
    std::cout << now_tm->tm_sec << ":";            // Giây

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::cout << ms.count() % 1000 << " ";  // Mili giây
}

Kernel kernel;

void task1_handler(Task* task) {
    int count = 1;
    while (1) {
        kernel.delay(1000);
        print_time();
        std::cout << "Task " << task->get_id()  << ": " << count << std::endl;

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
        kernel.delay(1000);
        print_time();
        std::cout << "Task " << task->get_id()  << ": " << count << std::endl;

        if (count == 30) {
            kernel.yield();
        }
        count++;
        if (count > 40)
            count = 20;
    }
}

void task3_handler(Task* task) {
    int count = 100;
    while (1) {
        kernel.delay(1000);
        print_time();
        std::cout << "Task " << task->get_id()  << ": " << count << std::endl;

        if (count == 20) {
            kernel.yield();
        }
        count--;
        if (count < 0)
            count = 100;
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
