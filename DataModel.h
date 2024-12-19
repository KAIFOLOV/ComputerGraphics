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
    Q_PROPERTY(QVector<QVector<QPointF>> faces READ faces NOTIFY facesChanged)

public:
    explicit DataModel(QObject *parent = nullptr);

    QVector<QPointF> vertices() const
    {
        return _vertices;
    }
    void setVertices(const QVector<QPointF> &newVertices);

    QVector<QPointF> edges() const
    {
        return _edges;
    }
    void setEdges(const QVector<QPointF> &newEdges);

    QVector<QVector<QPointF>> faces() const;
    void setFaces(const QVector<QVector<QPointF>> &newFaces);

    void updateData(const QVector<QVector<float>> &vertices, int steps);

signals:
    void verticesChanged();
    void edgesChanged();
    void facesChanged();

private:
    QVector<QPointF> _vertices;
    QVector<QPointF> _edges;
    QVector<QVector<QPointF>> _faces;
};

#endif // DATAMODEL_H
