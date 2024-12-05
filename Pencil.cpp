#include "Pencil.h"
#include "qdebug.h"

Pencil::Pencil(const QVector<QVector3D> &vertices) : _vertices(vertices.size(), 4)
{
    for (uint32_t j = 0; j < vertices.size(); j++) {
        _vertices[j][0] = vertices.value(j).x();
        _vertices[j][1] = vertices[j].y();
        _vertices[j][2] = vertices[j].z();
        _vertices[j][3] = 1;
    }
}

void Pencil::Translate(const float x, const float y, const float z)
{
    Matrix translation {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 },
    };

    _vertices = _vertices * translation;
}

void Pencil::Rotate(float roll, float yaw, float pitch)
{
    float s, c;

    // roll
    roll *= M_PI / 180;

    s = sin(roll);
    c = cos(roll);

    Matrix R_x {
        { 1, 0, 0, 0 },
        { 0, c, -s, 0 },
        { 0, s, c, 0 },
        { 0, 0, 0, 1 },
    };

    // yaw
    yaw *= M_PI / 180;

    s = sin(yaw);
    c = cos(yaw);

    Matrix R_y {
        { c, 0, s, 0 },
        { 0, 1, 0, 0 },
        { -s, 0, c, 0 },
        { 0, 0, 0, 1 },
    };

    // pitch
    pitch *= M_PI / 180;

    s = sin(pitch);
    c = cos(pitch);

    Matrix R_z {
        { c, -s, 0, 0 },
        { s, c, 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 },
    };

    _vertices = _vertices * R_x * R_y * R_z;
}

Matrix Pencil::vertices() const
{
    return _vertices;
}

QVector<QVector<uint32_t>> Pencil::edges() const
{
    return _edges;
}

void Pencil::setEdges(const QVector<QVector<uint32_t>> &newEdges)
{
    _edges = newEdges;
}
