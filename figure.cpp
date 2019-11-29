#include "figure.h"
//#include <iostream>


Figure::Figure(TriangPoints figure, QPainter *inPainter, QSize VirtualCanvas, QSize Canvas , const float distansFromCanvas) :
    structure(figure),
    painter(inPainter),
    virtualCanvas(VirtualCanvas),
    canvas(Canvas),
    distans(distansFromCanvas)
{}


void Figure::Render()
{    

    vector<QVector3D> canvasPoints;    // Массив все точек фигуры на кавасе
    for (auto point: structure.points) {
        canvasPoints.push_back(InCanvasDemention(point));
    }

    float **zbuffer = new float*[canvas.width()];
    for (int var = 0; var < canvas.width(); var++) {
        zbuffer[var] = new float[canvas.height()];
        for (int i = 0; i < canvas.height(); i++) {
            zbuffer[var][i] = std::numeric_limits<float>::max();
        }
    }


    for (auto triangle: structure.modTriangle) {

        painter->setPen(QPen(triangle.color, 1));
        DrawFilledTriangle(
                    canvasPoints[triangle.triangle[0]],
                    canvasPoints[triangle.triangle[1]],
                    canvasPoints[triangle.triangle[2]],
                    zbuffer
                    );
//        painter->setPen(QPen(Qt::black, 1));
//        DrawWireframeTriangle(
//                    canvasPoints[triangle.triangle[0]],
//                    canvasPoints[triangle.triangle[1]],
//                    canvasPoints[triangle.triangle[2]]
//                    );
    }
    for (int var = 0; var < canvas.width(); var++) {
        delete zbuffer[var];
    }
    delete zbuffer;

}

void Figure::Move(QVector3D shift)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        structure.points[i] += shift;
    }
}


void Figure::RotateX(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        QVector3D tmp = structure.points[i];
        structure.points[i].setX(tmp.x());
        structure.points[i].setY(tmp.y()*cos(angle) + tmp.z()*sin(angle));
        structure.points[i].setZ(-tmp.y()*sin(angle) + tmp.z()*cos(angle));
    }
}

void Figure::RotateY(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        QVector3D tmp = structure.points[i];
        structure.points[i].setX(tmp.x()*cos(angle) + tmp.z()*sin(angle));
        structure.points[i].setY(tmp.y());
        structure.points[i].setZ(-tmp.x()*sin(angle) + tmp.z()*cos(angle));
    }
}

void Figure::RotateZ(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        QVector3D tmp = structure.points[i];
        structure.points[i].setX(tmp.x()*cos(angle) - tmp.y()*sin(angle));
        structure.points[i].setY(-tmp.x()*sin(angle) + tmp.y()*cos(angle));
        structure.points[i].setZ(tmp.z());
    }
}


void Figure::DrawFilledTriangle(QVector3D P0, QVector3D P1, QVector3D P2, float** zbuffer) {
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
        if (A.x() > B.x()) std::swap(A, B);
        for (int j = A.x(); j <= B.x(); j++) {
            float phi = B.x() == A.x() ? 1. : (j - A.x()) / (float)(B.x() - A.x());
            QVector3D P = QVector3D(A) + QVector3D(B-A) * phi;
//            cout << "( " << roundf(P.x()) << ", " << roundf(P.y()) << " ), ";
            if (zbuffer[int(P.x())][int(P.y())] > P.z()) {
                zbuffer[int(P.x())][int(P.y())] = P.z();
                painter->drawPoint(int(P.x()), int(P.y()));

            }
        }
    }
 }


void Figure::DrawWireframeTriangle(QVector3D P0, QVector3D P1, QVector3D P2) {
    painter->drawLine(P0.x(), P0.y(), P1.x(), P1.y());
    painter->drawLine(P1.x(), P1.y(), P2.x(), P2.y());
    painter->drawLine(P2.x(), P2.y(), P0.x(), P0.y());
}

QVector3D Figure::ViewportToCanvas(float x, float y, float z) {    // Масштабирование координат для отображения на настоящем конвасе
      return QVector3D((x * canvas.width() / virtualCanvas.width() + canvas.width()/2), (-y * canvas.height() / virtualCanvas.height() + canvas.height()/2), z);
}

QVector3D Figure::InCanvasDemention(QVector3D point) {    // Переводит все в координаты канваса
      return ViewportToCanvas(point.x() * distans / point.z(), point.y() * distans / point.z(), point.z());
}
