#ifndef TRIANG_POINTS_H
#define TRIANG_POINTS_H

#include <vector>

#include <QVector3D>
#include <QColor>

struct Triangle {
    int triangle[3];
    QColor color;
};

struct TriangPoints {
    std::vector<QVector3D> points;
    std::vector<Triangle> modTriangle;
};




#endif // TRIANG_POINTS_H
