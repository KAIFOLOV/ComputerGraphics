#ifndef PENCIL_H
#define PENCIL_H

#include <QObject>

struct Vertice
{
    Vertice(const float x, const float y, const float z) : _x(x), _y(y), _z(z)
    {}

    float _x;
    float _y;
    float _z;
};

struct Edge
{
    Edge(const int vertice1, const int vertice2) : _vertice1(vertice1), _vertice2(vertice2)
    {}

    int _vertice1;
    int _vertice2;
};

class Pencil : public QObject
{
    Q_OBJECT
public:
    explicit Pencil(QObject *parent = nullptr);

    QVector<Vertice> vertices() const;

    QVector<Edge> edges() const;

private:
    QVector<Vertice> _vertices;
    QVector<Edge> _edges;

    void initializePencil();
};

#endif // PENCIL_H
