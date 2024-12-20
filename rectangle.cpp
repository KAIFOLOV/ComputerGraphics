#include "rectangle.h"

Rectangle::Rectangle(QObject *parent) : QObject(parent)
{
    _vertices = { { 100, 200 }, { 197, 225 }, { 210, 177 }, { 113, 152 } };
    _edges = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } };
}

void Rectangle::setVertices(const QVector<QPointF> &points)
{
    _vertices = points;
    emit verticesChanged();
}

void Rectangle::setEdges(const QVector<QPointF> &edges)
{
    _edges = edges;
}

QVector<QPointF> Rectangle::vertices() const
{
    return _vertices;
}

QVector<QPointF> Rectangle::edges() const
{
    return _edges;
}

void Rectangle::translate(double dx, double dy)
{
    for (auto &point : _vertices) {
        point.rx() += dx;
        point.ry() += dy;
    }
    emit verticesChanged();
}

void Rectangle::rotate(double angle)
{
    QPointF pivot = _vertices[findBottomRightVertex()];

    double angleRad = qDegreesToRadians(angle);

    double cosA = qCos(angleRad);
    double sinA = qSin(angleRad);

    for (auto &point : _vertices) {
        double xShifted = point.x() - pivot.x();
        double yShifted = point.y() - pivot.y();

        double xRotated = xShifted * cosA - yShifted * sinA;
        double yRotated = xShifted * sinA + yShifted * cosA;

        point.setX(xRotated + pivot.x());
        point.setY(yRotated + pivot.y());
    }

    emit verticesChanged();
}

int Rectangle::findBottomRightVertex() const
{
    int bottomRightIndex = 0;
    double maxSum = _vertices[0].x() + _vertices[0].y();

    for (int i = 1; i < _vertices.size(); ++i) {
        double sum = _vertices[i].x() + _vertices[i].y();
        if (sum > maxSum) {
            maxSum = sum;
            bottomRightIndex = i;
        }
    }
    return bottomRightIndex;
}

void Rectangle::reset()
{
    _vertices = { { 100, 200 }, { 197, 225 }, { 210, 177 }, { 113, 152 } };
    emit verticesChanged();
}
