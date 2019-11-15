#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include <QColor>
#include <QSize>

#include <cmath>

#include "figure.h"
#include "triang_points.h"
#include "parallelepipe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    int i = 0;
    QPixmap *scene;
    QPainter *painter;

    QSize Canvas = QSize(900, 900);
    QSize VirtualCanvas = QSize(1, 1);
    const float DistanceToVirtualCanvas = 1;

    TriangPoints TP_Parallelepipe = {
        {
//            {1,1,1},
//            {1,1,2},
//            {2,1,2},
//            {2,1,1},
//            {1,2,1},
//            {1,2,2},
//            {2,2,2},
//            {2,2,1}



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

            {{0, 1, 2}, Qt::red},
            {{0, 2, 3}, Qt::red},
            {{4, 0, 3}, Qt::green},
            {{4, 3, 7}, Qt::green},
            {{5, 4, 7}, Qt::blue},
            {{5, 7, 6}, Qt::blue},
            {{1, 5, 6}, Qt::yellow},
            {{1, 6, 2}, Qt::yellow},
            {{4, 5, 1}, Qt::magenta},
            {{4, 1, 0}, Qt::magenta},
            {{2, 6, 7}, Qt::gray},
            {{2, 7, 3}, Qt::gray}



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
};
#endif // MAINWINDOW_H
