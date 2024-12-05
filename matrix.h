#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>
#include <QVector>

class Matrix : public QVector<QVector<float>>
{
public:
    Matrix(const uint32_t rows, const uint32_t columns);
    Matrix(const std::initializer_list<QVector<float>> &matrix);

    const Matrix operator*(const Matrix &obj) const;

    uint32_t getRows() const;
    uint32_t getColumns() const;

private:
    uint32_t _rows;
    uint32_t _columns;
};

#endif // MATRIX_H
