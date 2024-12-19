#include "DataModel.h"

DataModel::DataModel(QObject *parent) : QObject(parent)
{}

void DataModel::setVertices(const QVector<QPointF> &newVertices)
{
    if (_vertices != newVertices) {
        _vertices = newVertices;
        emit verticesChanged();
    }
}

void DataModel::setEdges(const QVector<QPointF> &newEdges)
{
    if (_edges != newEdges) {
        _edges = newEdges;
        emit edgesChanged();
    }
}

QVector<QVector<QPointF>> DataModel::faces() const
{
    return _faces;
}

void DataModel::setFaces(const QVector<QVector<QPointF>> &newFaces)
{
    if (_faces != newFaces) {
        _faces = newFaces;
        emit facesChanged();
    }
}

void DataModel::updateData(const QVector<QVector<float>> &vertices, int steps)
{
    _vertices.clear();
    _edges.clear();

    for (const auto &vertex : vertices) {
        _vertices.append(QPointF(vertex[0], vertex[1]));
    }

    for (int z = 0; z < steps - 1; ++z) {
        for (int x = 0; x < steps - 1; ++x) {
            int idx = z * steps + x;
            // Добавление ребер между соседними точками
            _edges.append(
             { static_cast<qreal>(idx), static_cast<qreal>(idx + 1) }); // Горизонтальное ребро
            _edges.append(
             { static_cast<qreal>(idx), static_cast<qreal>(idx + steps) }); // Вертикальное ребро
        }
    }

    emit verticesChanged();
    emit edgesChanged();
}
