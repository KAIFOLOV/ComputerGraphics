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

QVector<QVector<QPointF> > DataModel::faces() const { return _faces; }

void DataModel::setFaces(const QVector<QVector<QPointF> > &newFaces)
{
    if (_faces != newFaces) {
        _faces = newFaces;
        emit facesChanged();
    }
}
