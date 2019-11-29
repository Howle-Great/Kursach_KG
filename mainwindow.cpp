#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->draw_label->setMouseTracking(true);
    this->setMouseTracking(true);

    scene = new QPixmap(900, 900);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    painter = new QPainter(scene);
    painter->setPen(QPen(Qt::black));

    FileManager file("/cylinder.obj");
    Object = file.Read();

    Figure* fig = new Figure(Object, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);

    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

    fig->Render();

    ui->draw_label->setPixmap(*scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    ui->draw_label->setPalette(Qt::white);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    switch (event->key()) {
        case Qt::Key_W:
            xAngle++;
            break;
        case Qt::Key_S:
            xAngle--;
            break;
        case Qt::Key_A:
            yAngle++;
            break;
        case Qt::Key_D:
            yAngle--;
            break;

    }

    Figure* fig = new Figure(Object, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

    fig->Render();
    ui->draw_label->setPixmap(*scene);

}


void MainWindow::on_pushButton_clicked() {
    string objectFilePath;

    if (ui->parallelepiped->isChecked()) {
        objectFilePath = "/parallelepipe.obj";
    } else if (ui->cube->isChecked()){
        objectFilePath = "/cube.obj";
    } else if (ui->cylinder->isChecked()){
        objectFilePath = "/cylinder.obj";
    }

    FileManager file(objectFilePath);
    Object = file.Read();

    ui->draw_label->setPalette(Qt::white);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    xAngle = 0;
    yAngle = 0;
    zAngle = 0;

    Figure* fig = new Figure(Object, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

    fig->Render();
    ui->draw_label->setPixmap(*scene);
}
