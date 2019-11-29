#include "figuresgenerator.h"



TriangPoints GenerateCylinder(float radius, float height, int Cx, int Cy, int grad, QVector3D shift) {
    // в верхнем круге центр - 0я точка
    // в нижнем круге центр - (grad + 1)я точка
    vector<QVector3D> points;     //2*(grad + 1)
    vector<Triangle> treangles;   //4*grad
    float x;
    float y;
    float z = 0;
    // генерируем передний круг
    points.push_back(QVector3D(Cx, Cy, z));     // 0
    for (int var = 0; var < grad; var++) {
        x = (float)Cx + radius*cos((var*M_PI/180)*(360/(float)grad));
        y = (float)Cy + radius*sin((var*M_PI/180)*(360/(float)grad));
        points.push_back(QVector3D(x, y, z));
    }
    // генерируем задний круг
    z = height;
    QVector3D deepShift(0, 0, z);
    points.push_back(QVector3D(Cx, Cy, z));     // grad + 1
    for (int var = 0; var < grad; var++) {
        points.push_back(points.at(var + 1) + deepShift);
    }
//    for (int var = 0; var < grad; var++) {
//        x = (float)Cx + radius*cos(var*(360/(float)grad));
//        y = (float)Cy + radius*sin(var*(360/(float)grad));
//        points.push_back(QVector3D(x, y, z));
//    }


    // соединяем треугольниками боковую часть цилиндра
    for (int var = 1; var < grad; var++) {
        treangles.push_back({{var, var + 1, var + grad + 1}, Qt::blue});
        treangles.push_back({{var + grad + 1, var + grad + 2, var + 1}, Qt::blue});
    }
    treangles.push_back({{grad, 1, 2*grad + 1}, Qt::blue});
    treangles.push_back({{2*grad + 1, grad + 2, 1}, Qt::blue});

    // соединяем треугольниками верхний круг
    int centerPoint = 0;
    for (int var = 1; var < grad; var++) {
        treangles.push_back({{centerPoint, var, var + 1}, Qt::green});
    }
    treangles.push_back({{centerPoint, grad, 1}, Qt::green});
    // соединяем треугольниками нижний круг
    centerPoint = grad+1;
    for (int var = grad + 2; var < 2*grad+1 ; var++) {
        treangles.push_back({{centerPoint, var, var + 1}, Qt::red});
    }
    treangles.push_back({{centerPoint, 2*grad+1, grad+2}, Qt::red});


    for (int var = 0; var < points.size(); var++) {
        points[var] += shift;
    }

    TriangPoints out;
    out.points = points;
    out.modTriangle = treangles;
    return out;
}


TriangPoints GenerateParallelepipe(float width, float height, float deep, QVector3D shift) {
    // в верхнем круге центр - 0я точка
    // в нижнем круге центр - (grad + 1)я точка
    vector<QVector3D> points(8);
    vector<Triangle> treangles(12);

    float z = 0;
    // генерируем переднюю сторону
    points[0] = QVector3D(0, 0, z);
    points[1] = QVector3D(width, 0, z);
    points[2] = QVector3D(width, height, z);
    points[3] = QVector3D(0, height, z);
    // генерируем заднюю сторону
    z = deep;
    for (int i = 4; i < 8; i++) {
        points[i] = points[i - 4] + QVector3D(0,0,z);
    }

    treangles = {
        {{0, 1, 2}, Qt::red},
        {{0, 3, 2}, Qt::red},
        {{1, 5, 6}, Qt::green},
        {{1, 2, 6}, Qt::green},
        {{5, 4, 7}, Qt::blue},
        {{5, 6, 7}, Qt::blue},
        {{4, 0, 3}, Qt::yellow},
        {{4, 7, 3}, Qt::yellow},

        {{2, 3, 7}, Qt::magenta},
        {{2, 6, 7}, Qt::magenta},

        {{1, 0, 4}, Qt::gray},
        {{1, 5, 4}, Qt::gray}
    };


    for (int var = 0; var < points.size(); var++) {
        points[var] += shift;
    }

    TriangPoints out;
    out.points = points;
    out.modTriangle = treangles;
    return out;
}
