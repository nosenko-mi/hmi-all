#include "fileutils.h"
#include "pointsserializer.h"



FileUtils::FileUtils() {}


int FileUtils::savePointsToFile(QString path, QVector<Point>* points){

    std::ofstream out(path.toStdString());
    if (out.is_open()) {
        PointsSerializer::serializePoints(*points, out);
    } else {
        // Handle error, e.g., print error message or exit program
        std::cerr << "Error opening file!" << std::endl;
        return -1; // Or throw an exception
    }
    out.close();

    return 1;
}

QVector<Point> FileUtils::openPointsFromFile(QString path){

}
