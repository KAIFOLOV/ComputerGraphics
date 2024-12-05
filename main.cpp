#include <QMainWindow>
#include <QApplication>

#include "camera.h"
#include "Pencil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.show();

    QVector<QVector3D> vertices;
    vertices.append(QVector3D(0, 0, 0));
    vertices.append(QVector3D(4, 0, 0));
    vertices.append(QVector3D(0, 4, 0));
    vertices.append(QVector3D(0, 0, 4));
    vertices.append(QVector3D(2, 0, 1));
    vertices.append(QVector3D(-2, 0, 1));
    vertices.append(QVector3D(2, 1, 0));
    vertices.append(QVector3D(-2, 1, 0));

    QVector<QVector<uint32_t>> edges;
    edges.append({ 1, 2 });
    edges.append({ 1, 3 });
    edges.append({ 1, 4 });
    edges.append({ 5, 6 });
    edges.append({ 7, 8 });

    Pencil pencil(vertices);
    pencil.setEdges(edges);

    Camera camera;
    camera.LookAt(3, 4, 6);

    auto tmp = pencil.vertices() * camera.view();

    return a.exec();
}
