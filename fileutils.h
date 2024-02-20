#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "point.h"
#include <fstream>
#include <iostream>

class FileUtils
{
public:
    FileUtils();

    static int savePointsToFile(QString path, QVector<Point>* points);
    static QVector<Point> openPointsFromFile(QString path);
};

#endif // FILEUTILS_H
