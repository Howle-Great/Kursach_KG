#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


void GenerateCylinder(float radius, float height, int Cx, int Cy, int grad) {
    // в верхнем круге центр - 0я точка
    // в нижнем круге центр - (grad + 1)я точка
    vector<QVector3D> points(2*(grad + 1));
    vector<Triangle> treangles(4*grad);
    float x;
    float y;
    float z = 0;
    // генерируем передний круг
    points[0] = QVector3D(Cx, Cy, z);
    for (int var = 0; var < grad; var++) {
        x = Cx + radius*cos(var*(360/grad));
        y = Cy + radius*sin(var*(360/grad));
        points.push_back(QVector3D(x, y, z));
    }
    // генерируем задний круг
    z = height;
    points[grad + 1] = QVector3D(Cx, Cy, z);
    for (int var = 0; var < grad; var++) {
        x = Cx + radius*cos(var*(360/grad));
        y = Cy + radius*sin(var*(360/grad));
        points.push_back(QVector3D(x, y, z));
    }
    // соединяем треугольниками верхний круг
    int centerPoint = 0;
    for (int var = 1; var < grad; var++) {
        treangles.push_back({{centerPoint, var, var + 1}, Qt::green});
    }
    // соединяем треугольниками нижний круг
    centerPoint = grad;
    for (int var = grad + 1; var < 2*grad; var++) {
        treangles.push_back({{centerPoint, var, var + 1}, Qt::red});
    }
    // соединяем треугольниками боковую часть цилиндра
    for (int var = grad + 1; var < 2*grad; var++) {
        treangles.push_back({{var, var + 1, var + grad + 1}, Qt::blue});
        treangles.push_back({{var + grad + 1, var + grad + 2, var + 1}, Qt::blue});
    }

    // Вывод в консоль
    std::cout << "sadfsf" << endl;
    std::cout << "Color: " << Qt::blue << endl;
//    for (int var = 0; var < points.size(); var++) {

//    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


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
//    GenerateCylinder(1, 1, 0, 0, 360);

//    painter->setPen(QPen(Qt::black));
    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
//    fig->Move({150, 150, 150});
//    fig->Move({-100, -50, 20});

//    fig->RotateY(i*M_PI/180);
//    fig->RotateX(5);

//    fig->Move({0, 0, 550});
    fig->Move({0, 0, 15});
    fig->Render();

    ui->draw_label->setPixmap(*scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
//    delete scene;
    ui->draw_label->setPalette(Qt::white);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
//    fig->Move({150, 150, 150});
//    fig->Move({-100, -50, 20});

    fig->RotateY(i++*M_PI/180);
    fig->RotateX(5);

//    fig->Move({0, 0, 550});
    fig->Move({0, 0, 15});
    fig->Render();
//    delete fig;

//    QVector3D point1 = {0,0,0};
//    QVector3D point2 = {1,0,0};
//    QVector3D point3 = {0,1,1};
//    painter->setPen(QPen(Qt::black));
//    std::cout << "RealasdasdAdsadADAD point is: ";
//    std::cout << "Real point is: " << painter << std::endl;
//    Parallelepipe* fig = new Parallelepipe(painter, point1, point2, point3);
//    fig->Draw();
//    std::cout << "Real point is: " << painter << std::endl;

    ui->draw_label->setPixmap(*scene);
    std::cout << "sadf" << std::endl;


}
