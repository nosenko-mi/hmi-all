#include "fileutils.h"
#include "qdebug.h"



FileUtils::FileUtils() {}


int FileUtils::savePointsToFile(QString path, QVector<Point>& points){

    QString text;
    foreach(Point p, points){
        text.append(p.toString());
    }
    std::ofstream out(path.toStdString());
    if (out.is_open()) {
        // PointsSerializer::serializePoints(*points, out);
        out << text.toStdString();
    } else {
        // Handle error, e.g., print error message or exit program
        std::cerr << "Error opening file!" << std::endl;
        return -1; // Or throw an exception
    }
    out.close();

    return 1;
}

QVector<Point> FileUtils::openPointsFromFile(QString path){

    QVector<Point> points;
    std::string line;
    std::ifstream in(path.toStdString());
    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        std::string xStr, yStr;
        iss >> xStr >> yStr;
        // if (!(iss >> x >> y)) { break; } // error
        double x = std::atof(xStr.c_str());

        double y = std::numeric_limits<double>::quiet_NaN();
        if (yStr != "nan"){
            y = std::atof(yStr.c_str());
        }
        points.append(Point(x,y));

        qDebug() << "Point: "  << x << " " << y;
    }
    return points;

}
