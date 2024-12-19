#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "Facets.h"
#include "Surface.h"
#include "camera.h"
#include "DataModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Surface surface(-2, 2, -2, 2, [](float x, float z) {
        return x * x + z * z;
    });

    Camera *camera = new Camera();
    camera->LookAt(3, 4, 6);
    camera->Ortho(400, 300, 50);

    DataModel *model = new DataModel();
    model->updateData(surface.vertices(), surface.steps());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/qml/lab4.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
