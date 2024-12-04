#include "matrix.h"

Matrix::Matrix(const uint32_t rows, const uint32_t columns) :
    _rows(rows),
    _columns(columns),
    _data(rows, QVector<float>(columns, 0.0))
{}

Matrix::Matrix(const std::initializer_list<QVector<float>> &matrix) :
    _data(matrix),
    _rows(matrix.size()),
    _columns(matrix.begin()->size())
{}

void Matrix::setValue(const uint32_t row, const uint32_t column, const double &value)
{
    if (row >= _rows || column >= _columns)
        throw std::out_of_range("Index out of bounds");
    _data[row][column] = value;
}

double Matrix::getValue(const uint32_t row, const uint32_t column) const
{
    if (row >= _rows || column >= _columns)
        throw std::out_of_range("Index out of bounds");
    return _data[row][column];
}

const Matrix Matrix::operator*(const Matrix &obj) const
{
    if (_columns != obj._rows)
        throw std::invalid_argument("Matrix dimensions do not allow multiplication");

    Matrix result(_rows, obj._columns);
    for (uint32_t i = 0; i < _rows; ++i) {
        for (uint32_t j = 0; j < obj._columns; ++j) {
            double sum = 0.0;
            for (uint32_t k = 0; k < _columns; ++k) {
                sum += _data[i][k] * obj._data[k][j];
            }
            result.setValue(i, j, sum);
        }
    }
    return result;
}

uint32_t Matrix::getRows() const
{
    return _rows;
}

uint32_t Matrix::getColumns() const
{
    return _columns;
}
