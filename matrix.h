#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <QVector>

class Matrix
{
public:
    Matrix(const uint32_t rows, const uint32_t columns);
    Matrix(const std::initializer_list<QVector<float>> &matrix);

    void setValue(const uint32_t row, const uint32_t column, const double &value);
    double getValue(const uint32_t row, const uint32_t column) const;

    const Matrix operator*(const Matrix &obj) const;

    uint32_t getRows() const;
    uint32_t getColumns() const;

private:
    uint32_t _rows;
    uint32_t _columns;
    QVector<QVector<float>> _data;
};

#endif // MATRIX_H
