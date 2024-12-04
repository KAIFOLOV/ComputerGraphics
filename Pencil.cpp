#include "Pencil.h"
#include <math.h>

Pencil::Pencil(QObject *parent) : QObject(parent)
{
    initializePencil();
}

void Pencil::initializePencil()
{
    _vertices.push_back({ 0, 0, 0 });
    _vertices.push_back({ 4, 0, 0 });
    _vertices.push_back({ 0, 4, 0 });
    _vertices.push_back({ 0, 0, 4 });
    _vertices.push_back({ 2, 0, 1 });
    _vertices.push_back({ -2, 0, 1 });
    _vertices.push_back({ 2, 1, 0 });
    _vertices.push_back({ -2, 1, 0 });

    _edges.push_back({ 1, 2 });
    _edges.push_back({ 1, 3 });
    _edges.push_back({ 1, 4 });
    _edges.push_back({ 5, 6 });
    _edges.push_back({ 7, 8 });
}

QVector<Vertice> Pencil::vertices() const
{
    return _vertices;
}

QVector<Edge> Pencil::edges() const
{
    return _edges;
}
