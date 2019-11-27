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


    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
//    fig->ReRender(xAngle, yAngle, zAngle, indent);
    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

    fig->Render();

    ui->draw_label->setPixmap(*scene);
//    delete fig;
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
        case Qt::Key_Q:
            zAngle++;
            break;
        case Qt::Key_E:
            zAngle--;
            break;

    }

    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

    fig->Render();
    ui->draw_label->setPixmap(*scene);
//    delete fig;
}


void MainWindow::on_pushButton_clicked() {
//    delete scene;
    ui->draw_label->setPalette(Qt::white);
    scene->fill(QColor("transparent"));
    scene->fill(QColor(Qt::white));

    Figure* fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
//    fig = new Parallelepipe(TP_Parallelepipe, painter, VirtualCanvas, Canvas, DistanceToVirtualCanvas);
    if (xAngle != 0) fig->RotateX(xAngle*M_PI/180);
    if (yAngle != 0) fig->RotateY(yAngle*M_PI/180);
    if (zAngle != 0) fig->RotateZ(zAngle*M_PI/180);

    if (indent != QVector3D(0,0,0)) {
        fig->Move(indent);
    }

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
