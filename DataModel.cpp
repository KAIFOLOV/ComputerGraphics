#include "DataModel.h"

DataModel::DataModel(QObject *parent)
    : QObject{parent}
{}

QVector<QPointF> DataModel::vertices() const
{
    return _vertices;
}

void DataModel::setVertices(const QVector<QPointF> &newVertices)
{
    _vertices = newVertices;
}

QVector<QPointF> DataModel::edges() const
{
    return _edges;
}

void DataModel::setEdges(const QVector<QPointF> &newEdges)
{
    _edges = newEdges;
}
