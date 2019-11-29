#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <QDir>

#include "triang_points.h"

using namespace std;

class FileManager {
public:
    FileManager(string name) :
        fileName(prefix + name),
        prefix(QDir::current().path().toStdString())
    {
        cout << prefix << endl;
    }
    ~FileManager() {}

    const string prefix;// = "/Users/howle/prog/2019.2/myProjects/CG/kursachFirst";
    string fileName;

    void Write(TriangPoints fig);
    TriangPoints Read();
    void Reopen(string name);

};

#endif // FILEMANAGER_H
