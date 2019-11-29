#ifndef FIGURESGENERATOR_H
#define FIGURESGENERATOR_H

#include <iostream>
#include <vector>
#include <QVector3D>
#include <cmath>

#include "triang_points.h"

using namespace std;

TriangPoints GenerateCylinder(float radius, float height, int Cx, int Cy, int grad, QVector3D shift);
TriangPoints GenerateParallelepipe(float width, float height, float deep, QVector3D shift);

#endif // FIGURESGENERATOR_H
