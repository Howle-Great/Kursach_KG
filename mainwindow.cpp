#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QSize>

//#include "painter.h"
#include "figure.h"
#include "triang_points.h"
#include "parallelepipe.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSize Canvas(900, 900);
    QSize VirtualCanvas(2, 2);
    const float DistanceToVirtualCanvas = 1;

    ui->setupUi(this);

    ui->draw_label->setPalette(Qt::white);
    ui->draw_label->setMouseTracking(true);
    this->setMouseTracking(true);

    scene = new QPixmap(900, 900);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    painter = new QPainter(scene);
    painter->setPen(QPen(Qt::black));
//    painter->drawLine(0,0,200,200);
    TriangPoints TP_Parallelepipe = {
        {
//            {1,1,1},
//            {1,1,100},
//            {100,1,100},
//            {100,1,1},
//            {1,100,1},
//            {1,100,100},
//            {100,100,100},
//            {100,100,1}



            {1,  1,  1},
            {-1,  1,  1},
            {-1, -1,  1},
            {1, -1,  1},
            {1,  1, -1},
            {-1,  1, -1},
            {-1, -1, -1},
            {1, -1, -1}
        },
        {

//            {{0, 1, 2}, Qt::red},
//            {{0, 2, 3}, Qt::gray},
//            {{4, 0, 3}, Qt::green},
//            {{4, 3, 7}, Qt::green},
//            {{5, 4, 7}, Qt::blue},
//            {{5, 7, 6}, Qt::blue},
//            {{1, 5, 6}, Qt::yellow},
//            {{1, 6, 2}, Qt::yellow},
            {{4, 5, 1}, Qt::magenta},
            {{4, 1, 0}, Qt::magenta},
//            {{2, 6, 7}, Qt::gray},
//            {{2, 7, 3}, Qt::gray}



//            {{0,1,3}, Qt::blue},
//            {{1,2,3}, Qt::blue},

//            {{0,3,4}, Qt::green},
//            {{1,0,5}, Qt::red},
//            {{2,1,6}, Qt::gray},
//            {{3,2,7}, Qt::magenta},

//            {{7,4,3}, Qt::green},
//            {{4,5,0}, Qt::red},
//            {{5,6,1}, Qt::gray},
//            {{6,7,2}, Qt::magenta},

//            {{5,4,7}, Qt::yellow},
//            {{5,6,7}, Qt::yellow}
        }
    };
//    painter->setPen(QPen(Qt::black));
    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
//    fig->Move({150, 150, 150});
//    fig->Move({-100, -50, 20});

//    fig->RotateY(45);
//    fig->RotateX(45);
//    fig->RotateZ(45);/

//    fig->Move({0, 0, 550});
    fig->Move({1, 1, 7});
    fig->Render();

    ui->draw_label->setPixmap(*scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
//    QVector3D point1 = {0,0,0};
//    QVector3D point2 = {1,0,0};
//    QVector3D point3 = {0,1,1};
//    painter->setPen(QPen(Qt::black));
//    std::cout << "RealasdasdAdsadADAD point is: ";
//    std::cout << "Real point is: " << painter << std::endl;
//    Parallelepipe* fig = new Parallelepipe(painter, point1, point2, point3);
//    fig->Draw();
//    std::cout << "Real point is: " << painter << std::endl;
//    ui->draw_label->setPixmap(*scene);
//    std::cout << "sadf" << std::endl;


}
