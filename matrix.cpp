#include "matrix.h"

Matrix::Matrix(const uint32_t rows, const uint32_t columns) :
    _rows(rows),
    _columns(columns),
    QVector<QVector<float>>(rows)
{
    for (auto &row : *this) {
        row.resize(columns);
    }
}

Matrix::Matrix(const std::initializer_list<QVector<float>> &matrix) :
    _rows(matrix.size()),
    _columns(matrix.begin()->size()),
    QVector<QVector<float>>(matrix)
{}

const Matrix Matrix::operator*(const Matrix &obj) const
{
    Matrix res(_rows, obj._columns);

    for (uint32_t j = 0; j < res._rows; j++) {
        for (uint32_t i = 0; i < res._columns; i++) {
            for (uint32_t k = 0; k < _columns; k++) {
                res[j][i] += (*this)[j][k] * obj[k][i];
            }
        }
    }
    return res;
}

uint32_t Matrix::getRows() const
{
    return _rows;
}

uint32_t Matrix::getColumns() const
{
    return _columns;
}
