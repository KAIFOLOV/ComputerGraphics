#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"

#include <QColor>

class Camera
{
public:
    Camera();

    const float x();
    const float y();
    const float z();

    const Matrix &view();
    const Matrix &projection();

    void LookAt(const float x, const float y, const float z);
    void Ortho(const float offsetX, float const offsetY, const float zoom);

private:
    float _x;
    float _y;
    float _z;

    Matrix _view;
    Matrix _projection;
};

#endif // CAMERA_H
