#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QPointF>

class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);

    Q_INVOKABLE QVector<QPointF> vertices() const;
    void setVertices(const QVector<QPointF> &newVertices);

    Q_INVOKABLE QVector<QPointF> edges() const;
    void setEdges(const QVector<QPointF> &newEdges);

private:
    /// Массив вершин
    QVector<QPointF> _vertices;
    /// Массив рёбер
    QVector<QPointF> _edges;
};

#endif // DATAMODEL_H
