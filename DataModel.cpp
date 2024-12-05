#include "DataModel.h"

DataModel::DataModel(QObject *parent)
    : QObject(parent)
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
