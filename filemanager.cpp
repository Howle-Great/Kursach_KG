#include "filemanager.h"

void FileManager::Write(TriangPoints fig) {
    ofstream file;
    file.open(fileName);
    if (file.is_open())
      {
        for (auto point : fig.points) {
            file << "v" << " " << point.x() << " " << point.y() << " " << point.z() << "\n";
        }

        file << "# " << fig.points.size() << " points\n\n";

        for (auto triangle : fig.modTriangle) {
            file << "t" << " " << triangle.triangle[0] << " " << triangle.triangle[1] << " " << triangle.triangle[2] << " " << triangle.color.name().toStdString() << " \n";
        }

        file << "# " << fig.modTriangle.size() << " triangles\n\n";

        file.close();
      }
      else cout << "Unable to open file";


}

TriangPoints FileManager::Read() {
    ifstream file;
    TriangPoints fig;
    file.open(fileName);

    if (file.is_open()) {
        string line;
        while (!file.eof()) {
            std::getline(file, line);
            std::istringstream iss(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                iss >> trash;
                QVector3D v;
                float tmpF;
                iss >> tmpF; v.setX(tmpF);
                iss >> tmpF; v.setY(tmpF);
                iss >> tmpF; v.setZ(tmpF);
                fig.points.push_back(v);
            } else if (!line.compare(0, 2, "t ")) {
                iss >> trash;

                Triangle tmp;

                iss >> tmp.triangle[0];
                iss >> tmp.triangle[1];
                iss >> tmp.triangle[2];

                string color;
                QString QScolor;
                bool ok;
                iss >> color;
                QScolor = QString::fromStdString(color);
                QScolor.remove(0,1);
                tmp.color = QColor(QScolor.toUInt(&ok,16));
                fig.modTriangle.push_back(tmp);
            }
        }
        file.close();
    } else cout << "Unable to open file";

    return fig;
}

void FileManager::Reopen(string name) {
    fileName = prefix + name;
}


