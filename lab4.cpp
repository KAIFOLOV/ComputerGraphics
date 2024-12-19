#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "Facets.h"
#include "Surface.h"
#include "camera.h"
#include "DataModel.h"
#include <math.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Camera *camera = new Camera();
    camera->LookAt(5, 6, 1);
    camera->Ortho(400, 300, 1);

    Surface surface(0, M_PI, 0, M_PI, [](float x, float z) {
        return sin(x) * sin(z);
    });
    surface.SetAngles(0, 0);

    Matrix vertices = surface.Scale() * camera->projection();

    DataModel *model = new DataModel();

    QVector<QPointF> tmpVertices;
    QVector<QPointF> tmpEdges;

    for (const auto &vertex : vertices) {
        tmpVertices.append(QPointF(vertex[0], vertex[1]));
    }

    int steps = surface.steps();

    for (int z = 0; z < steps - 1; ++z) {
        for (int x = 0; x < steps - 1; ++x) {
            int idx = z * steps + x;
            tmpEdges.append(
             { static_cast<qreal>(idx), static_cast<qreal>(idx + 1) });
            tmpEdges.append(
             { static_cast<qreal>(idx), static_cast<qreal>(idx + steps) });
        }
    }

    model->setEdges(tmpEdges);
    model->setVertices(tmpVertices);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/qml/lab4.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
