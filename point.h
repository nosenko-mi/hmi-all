#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <QPointF>

class Point
{
public:
    Point();
    Point(double x, double y);

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
