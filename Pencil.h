#ifndef PENCIL_H
#define PENCIL_H

#include "matrix.h"

#include <QObject>
#include <QVector3D>

class Pencil
{
public:
    explicit Pencil(const QVector<QVector3D> &vertices);

    void Translate(const float x, const float y, const float z);
    void Rotate(float roll, float pitch, float yaw);

    Matrix vertices() const;

    QVector<QPointF> edges() const;
    void setEdges(const QVector<QPointF> &newEdges);

private:
    Matrix _vertices;
    QVector<QPointF> _edges;
};

#endif // PENCIL_H
