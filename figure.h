#ifndef FIGURE_H
#define FIGURE_H


#include <vector>
#include <cmath>

#include <iostream>

#include <QVector3D>
#include <QColor>
#include <QPainter>
#include <QSize>
#include <QPoint>
#include <QPen>

#include "triang_points.h"

using namespace std;

class Figure
{
public:
    Figure(TriangPoints figure, QPainter *inPainter, QSize VirtualCanvas, QSize Canvas , const float distansFromCanvas);
    ~Figure() {}

    void Render();    // отрисовывает всеобъекты

    void Move(QVector3D shift);    // перенос всего объекта

    void RotateX(float angle);  // разворот объекта
    void RotateY(float angle);
    void RotateZ(float angle);

    void ReRender(int &xAngle, int &yAngle, int &zAngle, QVector3D indent);

private:
    TriangPoints structure; // структура объекта
    QPainter *painter;
    QSize virtualCanvas;  // Плоскость в пространстве на которую проецируется объекты
    QSize canvas;   // Холст на котором все отображается
    const float distans;  // Растояние от (0, 0, 0) до virtualCanvas


    QVector3D InCanvasDemention(QVector3D point);

    QVector3D ViewportToCanvas(float x, float y, float z);

    void DrawWireframeTriangle(QVector3D P0, QVector3D P1, QVector3D P2);

    void DrawFilledTriangle(QVector3D P0, QVector3D P1, QVector3D P2, float** zbuffer);

};


#endif // FIGURE_H
