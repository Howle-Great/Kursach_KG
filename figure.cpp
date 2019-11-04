#include "figure.h"
#include <iostream>

void Figure::Render()
{    

    vector<QPoint> canvasPoints;    // Массив все точек фигуры на кавасе
    for (auto point: structure.points) {
        canvasPoints.push_back(InCanvasDemention(point));
    }

    for (auto triangle: structure.modTriangle) {
        painter->setPen(QPen(triangle.color, 3));
//        DrawFilledTriangle(
//                    canvasPoints[triangle.triangle[0]],
//                    canvasPoints[triangle.triangle[1]],
//                    canvasPoints[triangle.triangle[2]]
//                    );
//        painter->setPen(QPen(Qt::black, 1));
        DrawWireframeTriangle(
                    canvasPoints[triangle.triangle[0]],
                    canvasPoints[triangle.triangle[1]],
                    canvasPoints[triangle.triangle[2]]
                    );
    }

    for (auto point: structure.points) {
//        std::cout << "( " << point.x() << ", " << point.y() << ", " << point.z() << " )" << std::endl;
    }

}

void Figure::Move(QVector3D shift)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        structure.points[i] += shift;
//        structure.points[i].setX(structure.points[i].x() + shift.x());
//        structure.points[i].setY(structure.points[i].y() + shift.y());
//        structure.points[i].setZ(structure.points[i].z() + shift.z());
    }
}


void Figure::RotateX(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        structure.points[i].setX(structure.points[i].x());
        structure.points[i].setY(structure.points[i].y()*cos(angle) + structure.points[i].z()*sin(angle));
        structure.points[i].setZ(-structure.points[i].y()*sin(angle) + structure.points[i].z()*cos(angle));
    }
}

void Figure::RotateY(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {

        structure.points[i].setX(structure.points[i].x()*cos(angle) + structure.points[i].z()*sin(angle));
        structure.points[i].setY(structure.points[i].y());
        structure.points[i].setZ(-structure.points[i].x()*sin(angle) + structure.points[i].z()*cos(angle));
    }
}

void Figure::RotateZ(float angle)
{
    for (auto i = 0; i < structure.points.size(); i++) {
        structure.points[i].setX(structure.points[i].x()*cos(angle) - structure.points[i].y()*sin(angle));
        structure.points[i].setY(-structure.points[i].x()*sin(angle) + structure.points[i].y()*cos(angle));
        structure.points[i].setZ(structure.points[i].z());
    }
}
