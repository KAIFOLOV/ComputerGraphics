#include "camera.h"

Camera::Camera() : _view(4, 4), _projection(4, 4)
{}

void Camera::LookAt(const float x, const float y, const float z)
{
    _x = x;
    _y = y;
    _z = z;

    Matrix T { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -x, -y, -z, 1 } };

    Matrix S { { -1.f, 0.f, 0.f, 0.f },
               { 0., 1.f, 0.f, 0.f },
               { 0.f, 0.f, 1.f, 0.f },
               { 0.f, 0.f, 0.f, 1.f } };

    Matrix R_90 { { 1, 0, 0, 0 }, { 0, 0, -1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 1 } };

    float s, c;
    float d = sqrt(x * x + y * y);

    if (d == 0) {
        c = 1;
        s = 0;
    } else {
        c = y / d;
        s = x / d;
    }

    Matrix R_u {
        { c, 0, s, 0 },
        { 0, 1, 0, 0 },
        { -s, 0, c, 0 },
        { 0, 0, 0, 1 },
    };

    float l = sqrt(d * d + z * z);

    if (l == 0) {
        c = 1;
        s = 0;
    } else {
        c = d / l;
        s = z / l;
    }

    Matrix R_w {
        { 1, 0, 0, 0 },
        { 0, c, -s, 0 },
        { 0, s, c, 0 },
        { 0, 0, 0, 1 },
    };

    _view = T * S * R_90 * R_u * R_w;
}

void Camera::Ortho(const float offsetX, float const offsetY, const float zoom)
{
    _projection = Matrix {
        { zoom, 0, 0, 0 },
        { 0, -zoom, 0, 0 },
        { 0, 0, 0, 0 },
        { offsetX, offsetY, 0, 1 },
    };
}