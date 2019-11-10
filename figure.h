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

private:
    TriangPoints structure; // структура объекта
    QPainter *painter;
    QSize virtualCanvas;  // Плоскость в пространстве на которую проецируется объекты
    QSize canvas;   // Холст на котором все отображается
    const float distans;  // Растояние от (0, 0, 0) до virtualCanvas

    void RotateZ(float angle);
    QPoint InCanvasDemention(QVector3D point) {    // Переводит все в координаты канваса
          return ViewportToCanvas(point.x() * distans / point.z(), point.y() * distans / point.z());
    }

    QPoint ViewportToCanvas(float x, float y) {    // Масштабирование координат для отображения на настоящем конвасе
          return QPoint((x * canvas.width() / virtualCanvas.width() + canvas.width()/2), (-y * canvas.height() / virtualCanvas.height() + canvas.height()/2));
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

    vector<QPoint> Interpolate (int x1, int y1, int x2, int y2) {
        vector<QPoint> values;
        // Определяет точки для рисования прямой между 2 точками
        if (x1 == x2) {
           int yMin = y1 < y2 ? y1 : y2;
           int yMax = y1 > y2 ? y1 : y2;
           for (int y = yMin; y <= yMax; y++) { values.push_back(QPoint(x1, y)); }
           return values;
        }

        if (y1 == y2) {
//           int xMin = x1 < x2 ? x1 : x2;
//           int xMax = xMin == x1 ? x2 : x1;
//           for (int x = xMin; x < xMax; x++) { values.push_back(QPoint(x, y2)); }
//           return values;
            return {QPoint(x1,y1)};
        }

        const int deltaX = abs(x2 - x1);
        const int deltaY = abs(y2 - y1);
        const int signX = x1 < x2 ? 1 : -1;
        const int signY = y1 < y2 ? 1 : -1;
        //
        int error = deltaX - deltaY;
        //
        QPoint lastPoint = QPoint(x1, y1);
        bool stateFistRound = true;
        while(x1 != x2 || y1 != y2)
        {
            if (lastPoint.y() == y1 && stateFistRound == false) {
                if (lastPoint.x() < x1) {
                    values.at(values.size() - 1) = QPoint(x1, y1);

                }
            } else {
                values.push_back(QPoint(x1, y1));
            }

            lastPoint = QPoint(x1, y1);

            const int error2 = error * 2;
            //
            if (error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
            stateFistRound = false;
        }
        values.push_back(QPoint(x2, y2));
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
        vector<QPoint> x01 = Interpolate(P0.x(), P0.y(), P1.x(), P1.y());
        vector<QPoint> x12 = Interpolate(P1.x(), P1.y(), P2.x(), P2.y());
        vector<QPoint> x02 = Interpolate(P0.x(), P0.y(), P2.x(), P2.y());
//        cout << "Просчитан 1 треугольник" << endl;
//        cout << "\nx01\n";
//        for (auto x: x01) {cout << "( " << x.x() << ", " << x.y() << " ), " << " ";}
//        cout << "\nx12\n";
//        for (auto x: x12) {cout << "( " << x.x() << ", " << x.y() << " ), " << " ";}
//        cout << "\nx02\n";
//        for (auto x: x02) {cout << "( " << x.x() << ", " << x.y() << " ), " << " ";}
//        cout << endl;
//        return;
//      Конкатенация коротких сторон
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

    cout <<endl;
//       Отрисовка горизонтальных отрезков

        for (int y = P0.y(); y <= P2.y(); y++) {
            cout << "( " << x_left[y - P0.y()].x() << ", " << x_left[y - P0.y()].y() << " ), "
                 << "( " << x_right[y - P0.y()].x() << ", " << x_right[y - P0.y()].y() << " ), ";
            painter->drawLine(x_left[y - P0.y()].x(), x_left[y - P0.y()].y() , x_right[y - P0.y()].x(), x_right[y - P0.y()].y() );
        }
        cout << "OUT" << endl;

    }

};


#endif // FIGURE_H
