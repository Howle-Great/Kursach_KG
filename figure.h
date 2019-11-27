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
    Figure(TriangPoints figure, QPainter *inPainter, QSize VirtualCanvas, QSize Canvas , const float distansFromCanvas) :
        structure(figure),
        painter(inPainter),
        virtualCanvas(VirtualCanvas),
        canvas(Canvas),
        distans(distansFromCanvas)
    {}
    ~Figure() {}

    void Render();    // отрисовывает всеобъекты

    void Move(QVector3D shift);    // перенос всего объекта
    void RotateX(float angle);  // разворот объекта
    void RotateY(float angle);

private:
    TriangPoints structure; // структура объекта
    QPainter *painter;
    QSize virtualCanvas;  // Плоскость в пространстве на которую проецируется объекты
    QSize canvas;   // Холст на котором все отображается
    const float distans;  // Растояние от (0, 0, 0) до virtualCanvas

    void RotateZ(float angle);
    QVector3D InCanvasDemention(QVector3D point) {    // Переводит все в координаты канваса
          return ViewportToCanvas(point.x() * distans / point.z(), point.y() * distans / point.z(), point.z());
    }

    QVector3D ViewportToCanvas(float x, float y, float z) {    // Масштабирование координат для отображения на настоящем конвасе
          return QVector3D((x * canvas.width() / virtualCanvas.width() + canvas.width()/2), (-y * canvas.height() / virtualCanvas.height() + canvas.height()/2), z);
    }

    void DrawWireframeTriangle(QVector3D P0, QVector3D P1, QVector3D P2) {
        painter->drawLine(P0.x(), P0.y(), P1.x(), P1.y());
        painter->drawLine(P1.x(), P1.y(), P2.x(), P2.y());
        painter->drawLine(P2.x(), P2.y(), P0.x(), P0.y());
    }

    void DrawFilledTriangle(QVector3D P0, QVector3D P1, QVector3D P2, float** zbuffer) {
        if (P0.y()==P1.y() && P0.y()==P2.y()) return; // если точка
        // сортируем точки по вертикали, P0, P1, P2 от меньшего к большему
        if (P0.y()>P1.y()) std::swap(P0, P1);
        if (P0.y()>P2.y()) std::swap(P0, P2);
        if (P1.y()>P2.y()) std::swap(P1, P2);
        cout << "( " << P0.x() << ", " << P0.y() << " ), "
             << "( " << P1.x() << ", " << P1.y() << " ), "
             << "( " << P2.x() << ", " << P2.y() << " ), "<< endl;

        float total_height = P2.y() - P0.y();
        for (int i = 0; i < roundf(total_height); i++) {

            bool second_half = i > (P1.y() - P0.y()) || P1.y() == P0.y();
            float segment_height = second_half ? (P2.y() - P1.y()) : (P1.y() - P0.y());

            float alpha = ((float)(i) / total_height);
            float beta  = ((float)(i)-(second_half ? P1.y() - P0.y() : 0))/segment_height; // be careful: with above conditions no division by zero here

            QVector3D A = P0 + QVector3D(P2-P0) * alpha;  // текущий сдвиг по осям x, y
            QVector3D B = second_half ? P1 + QVector3D(P2-P1) * beta : P0 + QVector3D(P1-P0) * beta;
            cout << "QVector3D B\n";
            if (A.x() > B.x()) std::swap(A, B);
            for (int j = A.x(); j <= B.x(); j++) {
                float phi = B.x() == A.x() ? 1. : (j - A.x()) / (float)(B.x() - A.x());
                QVector3D P = QVector3D(A) + QVector3D(B-A) * phi;
                cout << "( " << roundf(P.x()) << ", " << roundf(P.y()) << " ), ";
                if (zbuffer[int(P.x())][int(P.y())] > P.z()) {
                    zbuffer[int(P.x())][int(P.y())] = P.z();
                    painter->drawPoint(int(P.x()), int(P.y()));

                }
            }
        }
     }

};


#endif // FIGURE_H
