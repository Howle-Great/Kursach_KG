#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include <QColor>
#include <QSize>

#include <QKeyEvent>

#include <cmath>

#include "figure.h"
#include "triang_points.h"
#include "parallelepipe.h"
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *scene;
    QPainter *painter;
    TriangPoints Object;
//    Figure* fig;

    int xAngle = 0;
    int yAngle = 0;
    int zAngle = 0;
    QVector3D indent = QVector3D(0, 0, 15);

    QSize Canvas = QSize(900, 900);
    QSize VirtualCanvas = QSize(1, 1);
    const float DistanceToVirtualCanvas = 1;

};
#endif // MAINWINDOW_H
