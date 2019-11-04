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

using std::vector;
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
    void RotateZ(float angle);

private:
    TriangPoints structure; // структура объекта
    QPainter *painter;
    QSize virtualCanvas;  // Плоскость в пространстве на которую проецируется объекты
    QSize canvas;   // Холст на котором все отображается
    const float distans;  // Растояние от (0, 0, 0) до virtualCanvas


    QPoint InCanvasDemention(QVector3D point) {    // Переводит все в координаты канваса
          return ViewportToCanvas(point.x() * distans / point.z(), point.y() * distans / point.z());
    }

    QPoint ViewportToCanvas(float x, float y) {    // Масштабирование координат для отображения на настоящем конвасе
          return QPoint((x * canvas.width() / virtualCanvas.width() + canvas.width()/2), (y * canvas.height() / virtualCanvas.height() + canvas.height()/2));
    }

    void DrawWireframeTriangle(QPoint P0, QPoint P1, QPoint P2) {
        cout << "Ghjcnj hbcjdrf\n";
        cout << "( " << P0.x() << ", " << P0.y() << " ), "
             << "( " << P1.x() << ", " << P1.y() << " ), "
             << "( " << P2.x() << ", " << P2.y() << " ), "<< endl;
        painter->drawLine(P0.x(), P0.y(), P1.x(), P1.y());
        painter->drawLine(P1.x(), P1.y(), P2.x(), P2.y());
        painter->drawLine(P2.x(), P2.y(), P0.x(), P0.y());
    }

    vector<QPoint> Interpolate (int y0, int x0, int y1, int x1) {
        // Определяет точки для рисования прямой между 2 точками
        if (y0 == y1) {
           return { QPoint(x0, y0) };
        }
        vector<QPoint> values;
        float dx = (x1 - x0),
              dy = (y1 - y0);
        cout << "A: " << dx << " " << dy <<"\n";
        float dX = x0;
        float dY = y0;
        for (int i = y0; i < y1; i++) {
            values.push_back(QPoint(dX, dY));
            dX += dx;
            dY += dy;
        }
        return values;
    }

    void DrawFilledTriangle(QPoint P0, QPoint P1, QPoint P2) {
        cout << "\nДо обработки" << "\n"
             << "( " << P0.x() << ", " << P0.y() << " ), "
             << "( " << P1.x() << ", " << P1.y() << " ), "
             << "( " << P2.x() << ", " << P2.y() << " ), "<< endl;
        // Сортировка точек так, что y0 <= y1 <= y2
        if (P1.y() < P0.y()) { swap(P1, P0); }
        if (P2.y() < P0.y()) { swap(P2, P0); }
        if (P2.y() < P1.y()) { swap(P2, P1); }
        cout << "После обработки" << "\n"
             << "( " << P0.x() << ", " << P0.y() << " ), "
             << "( " << P1.x() << ", " << P1.y() << " ), "
             << "( " << P2.x() << ", " << P2.y() << " ), "<< endl;


        // Вычисление координат x рёбер треугольника
        vector<QPoint> x01 = Interpolate(P0.y(), P0.x(), P1.y(), P1.x());
        vector<QPoint> x12 = Interpolate(P1.y(), P1.x(), P2.y(), P2.x());
        vector<QPoint> x02 = Interpolate(P0.y(), P0.x(), P2.y(), P2.x());

        // Конкатенация коротких сторон
        vector<QPoint> x012;
        copy(x01.begin(), x01.end(), std::back_inserter(x012));
        copy(x12.begin(), x12.end(), std::back_inserter(x012));

        // Определяем, какая из сторон левая и правая
        vector<QPoint> x_left;
        vector<QPoint> x_right;
        float medium = x012.size() / 2;

        if (x02[medium].x() < x012[medium].x()) {
            x_left = x02;
            x_right = x012;
        } else {
            x_left = x012;
            x_right = x02;
        }
//        for (auto el:x_left) {cout << "Left: " << el << endl;}
//        cout << "\nx_right\n";
//        for (auto el:x_right) {cout << "Right: " << el << endl;}


//        cout << "Точки" << endl;
        // Отрисовка горизонтальных отрезков
        for (int y = P0.y(); y < P2.y(); y++) {
            for (int x = x_left[y - P0.y()].x(); x < x_right[y - P0.y()].x(); x++) {
                painter->drawPoint(QPoint(x_left[y - P0.y()].x(), x_left[y - P0.y()].y()));
                cout << "( " << x_left[y - P0.y()].x() << ", " << x_left[y - P0.y()].y() << " ), ";
            }
//            int tmp = x_left[y - P0.y()];
//            cout << tmp << "\n";
        }


    }

};


#endif // FIGURE_H
