#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QVector>
#include <QPointF>
#include <QMatrix4x4>
#include <QObject>

class Rectangle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> vertices READ vertices NOTIFY verticesChanged)

public:
    Rectangle(QObject *parent = nullptr);

    /// Установка вершин
    Q_INVOKABLE void setVertices(const QVector<QPointF> &points);
    /// Установка ребер
    Q_INVOKABLE void setEdges(const QVector<QPointF> &edges);
    /// Получение вершин
    Q_INVOKABLE QVector<QPointF> vertices() const;
    /// Получение ребер
    Q_INVOKABLE QVector<QPointF> edges() const;
    /// Сдвиг
    Q_INVOKABLE void translate(double dx, double dy);
    /// Поворота
    Q_INVOKABLE void rotate(double angle);
    /// Вспомогательная функция для поиска правой нижней вершины
    Q_INVOKABLE int findBottomRightVertex() const;
    /// Сброс до начальных вершин
    Q_INVOKABLE void reset();

signals:
    /// Сигнал об изменении положения вершин
    void verticesChanged();

private:
    /// Массив вершин
    QVector<QPointF> _vertices;
    /// Массив рёбер
    QVector<QPointF> _edges;
};

#endif // RECTANGLE_H
