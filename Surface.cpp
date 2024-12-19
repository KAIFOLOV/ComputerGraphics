#include "Surface.h"

Surface::Surface(
 float x_min, float x_max, float z_min, float z_max, float (*equation)(float x, float z)) :
    _corners {
        { x_min, 0, z_min, 1 },
        { x_max, 0, z_min, 1 },
        { x_min, 0, z_max, 1 },
        { x_max, 0, z_max, 1 },
    },
    _rotation(4, 4),
    _vertices(_steps * _steps, 4)
{
    uint32_t v = 0;

    float z = z_min;

    for (int32_t j = 0; j < _steps; j++) {
        float x = x_min;

        for (int32_t i = 0; i < _steps; i++) {
            _vertices[v][0] = x;
            _vertices[v][1] = equation(x, z);
            _vertices[v][2] = z;
            _vertices[v][3] = 1;

            v++;

            x += (x_max - x_min) / _steps;
        }

        z += (z_max - z_min) / _steps;
    }
}

void Surface::SetAngles(float roll, float pitch)
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

    // pitch
    pitch *= M_PI / 180;

    s = sin(pitch);
    c = cos(pitch);

    Matrix R_y {
        { c, 0, s, 0 },
        { 0, 1, 0, 0 },
        { -s, 0, c, 0 },
        { 0, 0, 0, 1 },
    };

    _rotation = R_y * R_x;
}

const Matrix Surface::Scale()
{
    const Matrix vertices = _vertices * _rotation;
    const Matrix corners = _corners * _rotation;

    float norm_x = abs((*std::max_element(corners.begin(), corners.end(),
                                          [](const QVector<float> &a, const QVector<float> &b) {
                                              return abs(a[0]) < abs(b[0]);
                                          }))[0]);

    float norm_y = abs((*std::max_element(vertices.begin(), vertices.end(),
                                          [](const QVector<float> &a, const QVector<float> &b) {
                                              return abs(a[1]) < abs(b[1]);
                                          }))[1]);

    float k = std::min(800 / 2 / norm_x, 600 / 2 / norm_y) - 1.0f;

    return vertices
           * Matrix {
                 { k, 0, 0, 0 },
                 { 0, k, 0, 0 },
                 { 0, 0, 0, 0 },
                 { 0, 0, 0, 1 },
             };
}

int Surface::steps()
{
    return _steps;
}

Matrix Surface::vertices() const
{
    return _vertices;
}
