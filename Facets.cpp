#include "Facets.h"

Facets::Facets(const QVector<QVector3D> &vertices, const QVector<QVector<uint32_t>> &faces)
    : Pencil(vertices),
    _faces(faces)
{
    updatePlanes();
}

void Facets::updatePlanes() {
    _planes.clear();
    _planes.resize(_faces.size());
    for (auto &p : _planes) {
        p.resize(4);
    }

    const auto &v = _vertices;

    std::array<float, 3> c {};

    for (uint8_t i = 0; i < 3; i++) {
        for (const auto &row : _vertices) {
            c[i] += row[i];
        }

        c[i] /= v.size();
    }

    for (uint32_t j = 0; j < _faces.size(); j++) {
        auto &f = _faces[j];
        auto &p = _planes[j];

        p[0] = (v[f[2]][1] - v[f[0]][1]) * (v[f[1]][2] - v[f[0]][2]) - (v[f[1]][1] - v[f[0]][1]) * (v[f[2]][2] - v[f[0]][2]);
        p[1] = (v[f[1]][0] - v[f[0]][0]) * (v[f[2]][2] - v[f[0]][2]) - (v[f[2]][0] - v[f[0]][0]) * (v[f[1]][2] - v[f[0]][2]);
        p[2] = (v[f[2]][0] - v[f[0]][0]) * (v[f[1]][1] - v[f[0]][1]) - (v[f[1]][0] - v[f[0]][0]) * (v[f[2]][1] - v[f[0]][1]);
        p[3] = -(p[0] * v[f[0]][0] + p[1] * v[f[0]][1] + p[2] * v[f[0]][2]);

        if (p[0] * c[0] + p[1] * c[1] + p[2] * c[2] + p[3] < 0) {
            p[0] = -p[0];
            p[1] = -p[1];
            p[2] = -p[2];
            p[3] = -p[3];
        }
    }
}

QVector<QVector<uint32_t>> Facets::faces() const
{
    return _faces;
}

QVector<QVector<float>> Facets::planes() const
{
    return _planes;
}

void Facets::Rotate(float roll, float pitch, float yaw)
{
    Pencil::Rotate(roll, pitch, yaw);
    updatePlanes();
}
