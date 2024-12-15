#ifndef FACETS_H
#define FACETS_H

#include "Pencil.h"

class Facets : public Pencil
{
public:
public:
    Facets(const QVector<QVector3D> &vertices, const QVector<QVector<uint32_t>> &faces);

    QVector<QVector<uint32_t>> faces() const;
    QVector<QVector<float>> planes() const;

    void Rotate(float roll, float pitch, float yaw) override;

    void updatePlanes();
private:
    QVector<QVector<uint32_t>> _faces;
    QVector<QVector<float>> _planes;
};

#endif // FACETS_H
