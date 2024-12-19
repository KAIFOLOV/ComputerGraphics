#ifndef SURFACE_H
#define SURFACE_H

#include "matrix.h"

class Surface
{
public:
    Surface(
     float x_min, float x_max, float z_min, float z_max, float (*equation)(float x, float z));

    const Matrix Scale();

    void SetAngles(const float roll, const float pitch);

    Matrix vertices() const;

    static int steps();

private:
    static constexpr int _steps = 10;

    Matrix _corners;
    Matrix _rotation;

    Matrix _vertices;
};

#endif // SURFACE_H
