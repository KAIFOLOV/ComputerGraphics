#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QPointF>
#include <QVector>

class DataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QPointF> vertices READ vertices NOTIFY verticesChanged)
    Q_PROPERTY(QVector<QPointF> edges READ edges NOTIFY edgesChanged)

public:
    explicit DataModel(QObject *parent = nullptr);

    QVector<QPointF> vertices() const { return _vertices; }
    void setVertices(const QVector<QPointF> &newVertices);

    QVector<QPointF> edges() const { return _edges; }
    void setEdges(const QVector<QPointF> &newEdges);

signals:
    void verticesChanged();
    void edgesChanged();

private:
    QVector<QPointF> _vertices;
    QVector<QPointF> _edges;
};

#endif // DATAMODEL_H
