#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Task.h"
#include "Scheduler.h"

int main(int argc, char *argv[])
{
    Task task1(1, 3, 2000);
    Task task2(2, 5, 1000);
    Task task3(3, 1, 500);

    Scheduler scheduler;
    scheduler.add_task(task1);
    scheduler.add_task(task2);
    scheduler.add_task(task3);

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

    return app.exec();
}
