#include <QMainWindow>
#include <QApplication>
#include <QQmlApplicationEngine>

#include "camera.h"
#include "Pencil.h"
#include "DataModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<QVector3D> vertices;
    vertices.append(QVector3D(0, 0, 0));
    vertices.append(QVector3D(4, 0, 0));
    vertices.append(QVector3D(0, 4, 0));
    vertices.append(QVector3D(0, 0, 4));
    vertices.append(QVector3D(2, 0, 1));
    vertices.append(QVector3D(-2, 0, 1));
    vertices.append(QVector3D(2, 1, 0));
    vertices.append(QVector3D(-2, 1, 0));

    QVector<QPointF> edges;
    edges.append({ 1, 2 });
    edges.append({ 1, 3 });
    edges.append({ 1, 4 });
    edges.append({ 5, 6 });
    edges.append({ 7, 8 });

    Pencil *pencil = new Pencil(vertices);
    pencil->setEdges(edges);

    Camera *camera = new Camera();
    camera->LookAt(3, 4, 6);
    camera->Ortho(50, 50, 10);

    QVector<QPointF> tmpVerticle;
    auto matrix = pencil->vertices() * camera->view() * camera->projection();
    for (int i = 0; i < matrix.size(); i++) {
        tmpVerticle.push_back({ matrix[i][0], matrix[i][1] });
    }

    DataModel *model = new DataModel();
    model->setVertices(tmpVerticle);
    model->setEdges(pencil->edges());

    return a.exec();
}
