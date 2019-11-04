#ifndef PARALLELEPIPE_H
#define PARALLELEPIPE_H

//#include <QVector3D>
//#include <QColor>
//#include <QPainter>
//#include <QSize>
//#include <QPoint>

#include "figure.h"
//#include "triang_points.h"

class Parallelepipe : public virtual Figure
{
public:
    Parallelepipe(TriangPoints figure, QPainter *inPainter, QSize VirtualCanvas, QSize Canvas , const float distansFromCanvas):Figure(figure, inPainter, VirtualCanvas, Canvas , distansFromCanvas){}

};

#endif // PARALLELEPIPE_H
