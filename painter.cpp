//#include "painter.h"
//#include <iostream>

////using namespace Parallelepipe;
//#define OFFSET_X -40
//#define OFFSET_Y -450

//Parallelepipe::Parallelepipe(QPainter *inPainter, QVector3D point1, QVector3D point2, QVector3D point3)
//{
//    basePoints[0] = point1;
//    basePoints[1] = point2;
//    basePoints[2] = point3;
//    painter = inPainter;
//}


//void Parallelepipe::Draw() {
//    CalculatePositions();

////    painter->setPen(Qt::black);
////    painter->drawLine(0, 0, 350, 350);


//    Rotate(90.0);
//    Move({300,100,100});

//    QPoint SecondDementionPoints[8];
//    ProjectToSecondDemention(SecondDementionPoints);

//    std::cout << "First Pack" << std::endl;

//    for (int i = 0; i < 3; i++) {
//        painter->setPen(Qt::blue);
//        painter->drawLine(SecondDementionPoints[i], SecondDementionPoints[i+1]);
//        std::cout << "( " << SecondDementionPoints[i].x() << ", " << SecondDementionPoints[i].y() << " )" << "\t"
//                  << "( " << SecondDementionPoints[i+1].x() << ", " << SecondDementionPoints[i+1].y() << " )" << std::endl;
//    }

//    std::cout << "Second Pack" << std::endl;

//    for (int i = 4; i < 7; i++) {
//        painter->drawLine(SecondDementionPoints[i], SecondDementionPoints[i+1]);
//        std::cout << "( " << SecondDementionPoints[i].x() << ", " << SecondDementionPoints[i].y() << " )" << "\t"
//                  << "( " << SecondDementionPoints[i+1].x() << ", " << SecondDementionPoints[i+1].y() << " )" << std::endl;
//    }

//    std::cout << "Therd Pack" << std::endl;

//    for (int i = 0; i < 4; i++) {
//        painter->drawLine(SecondDementionPoints[i], SecondDementionPoints[i+4]);
//        std::cout << "( " << SecondDementionPoints[i].x() << ", " << SecondDementionPoints[i].y() << " )" << "\t"
//                  << "( " << SecondDementionPoints[i+4].x() << ", " << SecondDementionPoints[i+4].y() << " )" << std::endl;
//    }

//}
//void Parallelepipe::Rotate(float angle) {

//    for (int i = 0; i < 8; i++) {
//        points[i].setX(points[i].x()*cos(angle) + points[i].z()*sin(angle));
//        points[i].setY(points[i].y());
//        points[i].setZ(-points[i].x()*sin(angle) + points[i].z()*cos(angle));
//    }
//    for (auto point: points) {

//    }
//}


//void Parallelepipe::Move(QVector3D shift) {
//    for (int i = 0; i < 8; i++) {
//        points[i] += shift;
//    }
//}

//void Parallelepipe::ProjectToSecondDemention(QPoint *SecondDementionPoints) {
//    for (int i = 0; i < 8; i++) {

//        SecondDementionPoints[i].setX((1)*int(points[i].x() - OFFSET_X));
//        SecondDementionPoints[i].setY((1)*int(points[i].y() - OFFSET_Y));
////        std::cout << "( " << SecondDementionPoints[i].x() << ", " << SecondDementionPoints[i].y() << " )" << std::endl;
//    }
//}
////QVector3D Parallelepipe::GiveBasesPoints()[] {}

//bool Parallelepipe::TestBasePointsLocation() {
//    bool allPointsOnXPlane = (basePoints[0].x() == basePoints[1].x() && basePoints[1].x() == basePoints[2].x());
//    bool allPointsOnYPlane = (basePoints[0].y() == basePoints[1].y() && basePoints[1].y() == basePoints[2].y());
//    bool allPointsOnZPlane = (basePoints[0].z() == basePoints[1].z() && basePoints[1].z() == basePoints[2].z());

//    /*
//     * Если все точки лежат в разных плоскостях, то мы можем вычислить расположение всех 8 точек параллепипеда
//     */
//    return (!allPointsOnXPlane || !allPointsOnYPlane || !allPointsOnZPlane);
//}

//void Parallelepipe::CalculatePositions() {
//    if (TestBasePointsLocation()) {
//        // Some collculations are there
//        QVector3D tmpPoints[8] = {
//            {0,0,0},
//            {0,0,100},
//            {100,0,100},
//            {100,0,0},
//            {0,100,0},
//            {0,100,100},
//            {100,100,100},
//            {100,100,0}
//        };

//        for (auto i = 0; i < sizeof (tmpPoints)/sizeof (QVector3D); i++) {
//            points[i] = tmpPoints[i];
//        }

//    }
//}
