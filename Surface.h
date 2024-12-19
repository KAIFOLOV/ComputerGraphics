#ifndef SURFACE_H
#define SURFACE_H

#include "matrix.h"

class Surface
{
public:
    Surface(
     float x_min, float x_max, float z_min, float z_max, float (*equation)(float x, float z));

    void SetAngles(const float roll, const float pitch);

    Matrix vertices() const;

    static int steps();

private:
    const Matrix Scale(const Matrix &vertices);

    static constexpr int _steps = 50;

    Matrix _corners;
    Matrix _rotation;

    Matrix _vertices;
};

#endif // SURFACE_H
