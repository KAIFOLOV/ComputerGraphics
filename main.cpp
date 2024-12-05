#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "camera.h"
#include "Pencil.h"
#include "DataModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<QVector3D> vertices;
    vertices.append(QVector3D(6, 0, 0));

    vertices.append(QVector3D(3, -1.154, 0));
    vertices.append(QVector3D(3, -0.577, -1));
    vertices.append(QVector3D(3, 0.577, -1));
    vertices.append(QVector3D(3, 1.154, 0));
    vertices.append(QVector3D(3, 0.577, 1));
    vertices.append(QVector3D(3, -0.577, 1));

    vertices.append(QVector3D(-6, -1.154, 0));
    vertices.append(QVector3D(-6, -0.577, -1));
    vertices.append(QVector3D(-6, 0.577, -1));
    vertices.append(QVector3D(-6, 1.154, 0));
    vertices.append(QVector3D(-6, 0.577, 1));
    vertices.append(QVector3D(-6, -0.577, 1));

    QVector<QPointF> edges;
    edges.append({1, 7});

    edges.append({1, 2});
    edges.append({2, 3});
    edges.append({3, 4});
    edges.append({4, 5});
    edges.append({5, 6});
    edges.append({6, 1});

    edges.append({7, 8});
    edges.append({8, 9});
    edges.append({9, 10});
    edges.append({10, 11});
    edges.append({11, 12});
    edges.append({12, 7});

    edges.append({0, 1});
    edges.append({0, 2});
    edges.append({0, 3});
    edges.append({0, 4});
    edges.append({0, 5});
    edges.append({0, 6});

    edges.append({2, 8});
    edges.append({3, 9});
    edges.append({4, 10});
    edges.append({5, 11});
    edges.append({6, 12});

    Pencil *pencil = new Pencil(vertices);
    pencil->setEdges(edges);

    Camera *camera = new Camera();
    camera->LookAt(3, 4, 6);
    camera->Ortho(400, 300, 50);

    QVector<QPointF> tmpVerticle;
    auto matrix = pencil->vertices() * camera->view() * camera->projection();
    for (int i = 0; i < matrix.size(); i++) {
        tmpVerticle.push_back({ matrix[i][0], matrix[i][1] });
    }

    DataModel *model = new DataModel();
    model->setVertices(tmpVerticle);
    model->setEdges(pencil->edges());

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [pencil, camera, model]() {
        qDebug() << "rotate";

        pencil->Rotate(15.0, 0.0, 0.0);
        QVector<QPointF> updatedVertices;
        auto updatedMatrix = pencil->vertices() * camera->view() * camera->projection();

        for (int i = 0; i < updatedMatrix.size(); i++) {
            updatedVertices.push_back({updatedMatrix[i][0], updatedMatrix[i][1]});
        }

        model->setVertices(updatedVertices);
    });
    timer.start(100);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/qml/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
