#ifndef POINTSSERIALIZER_H
#define POINTSSERIALIZER_H

#include "point.h"
#include "qdebug.h"


class PointsSerializer
{
public:
    static bool serializePoints(const QVector<Point>& points, std::ofstream& stream) {

        qDebug() << "PointsSerializer::serializePoints";
        stream << points.size() << std::endl; // Write vector size
        for (const Point& point : points) {
            if (!point.serialize(stream)) {
                return false;
            }
        }
        qDebug() << "PointsSerializer::serializePoints end";
        return stream.good();
    }

    // Deserialize QVector<Point> (optional)
    static bool deserializePoints(std::ifstream& stream, QVector<Point>& points) {
        size_t numPoints;
        stream >> numPoints;
        points.resize(numPoints);
        for (int i = 0; i < numPoints; ++i) {
            if (!Point::deserialize(stream, points[i])) {
                return false;
            }
        }
        return stream.good();
    }
    PointsSerializer();
};

#endif // POINTSSERIALIZER_H
