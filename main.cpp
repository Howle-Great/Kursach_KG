#include "mainwindow.h"

#include <QApplication>

#include "filemanager.h"
#include "figuresgenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager file("objects/cylinder.obj");
    file.Write(GenerateCylinder(1, 2, -1, 0, 120, QVector3D(0, 0, 0)));
    file.Reopen("objects/cube.obj");
    file.Write(GenerateParallelepipe(2, 2, 2, QVector3D(-1, -1, -1)));
    file.Reopen("objects/parallelepipe.obj");
    file.Write(GenerateParallelepipe(2, 2, 3, QVector3D(-1, -1, -1)));

    MainWindow w;
    w.show();
    return a.exec();
}
