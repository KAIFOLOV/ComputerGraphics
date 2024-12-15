#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "Facets.h"
#include "camera.h"
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

    QVector<QVector<uint32_t>> faces;
    faces.append({ 0, 6, 1 });
    faces.append({ 6, 12, 7, 1 });

    faces.append({ 0, 5, 6 });
    faces.append({ 5, 11, 12, 6 });

    faces.append({ 2, 8, 9, 3 });
    faces.append({ 0, 2, 3 });

    faces.append({ 0, 1, 2 });
    faces.append({ 1, 7, 8, 2 });

    faces.append({ 0, 4, 5 });
    faces.append({ 4, 10, 11, 5 });

    faces.append({ 0, 3, 4 });
    faces.append({ 3, 9, 10, 4 });

    faces.append({ 7, 8, 9, 10, 11, 12 });

    Facets *pencil = new Facets(vertices, faces);

    Camera *camera = new Camera();
    camera->LookAt(3, 4, 6);
    camera->Ortho(400, 300, 50);

    auto matrix = pencil->vertices() * camera->view() * camera->projection();
    QVector<QVector<QPointF>> tmpFaces;

    for (int i = 0; i < pencil->faces().size(); i++)
    {
        auto face = pencil->faces()[i];
        auto plane = pencil->planes()[i];

        if (plane[0] * camera->x() + plane[1] * camera->y() + plane[2] * camera->z() < 0) {
            QVector<QPointF> tmpFace;

            for (uint32_t i = 0; i < face.size(); i++) {
                tmpFace.push_back( {matrix[face[i]][0], matrix[face[i]][1] });
            }
            tmpFaces.append(tmpFace);
        }
    }

    DataModel *model = new DataModel();
    model->setFaces(tmpFaces);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [pencil, camera, model]() {
        qDebug() << "rotate";

        pencil->Rotate(2, 0.0, 0.0);
        auto updatedMatrix = pencil->vertices() * camera->view() * camera->projection();
        QVector<QVector<QPointF>> updateFaces;

        for (int i = 0; i < pencil->faces().size(); i++)
        {
            auto face = pencil->faces()[i];
            auto plane = pencil->planes()[i];

            if (plane[0] * camera->x() + plane[1] * camera->y() + plane[2] * camera->z() < 0) {
                QVector<QPointF> updateFace;

                for (uint32_t i = 0; i < face.size(); i++) {
                    updateFace.push_back( {updatedMatrix[face[i]][0], updatedMatrix[face[i]][1] });
                }
                updateFaces.append(updateFace);
            }
        }

        model->setFaces(updateFaces);
    });
    timer.start(100);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/qml/qml/lab3.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
