#include "rectangle.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Rectangle>("CustomShapes", 1, 0, "Rectangle");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/qml/lab1.qml"));
    QObject::connect(
     &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
     []() {
         QCoreApplication::exit(-1);
     },
     Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
