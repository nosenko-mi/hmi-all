#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QPointF>
#include <fstream>

class Point
{
public:
    Point();
    Point(double x, double y);

    bool serialize(std::ofstream& stream) const;

    static bool deserialize(std::ifstream& stream, Point& point);

    void setX(double x);
    void setY(double y);

    double getX();
    double getY();

    QPointF toQPointF();
    bool isValid();

private:
    double x;
    double y;

};

#endif // POINT_H
