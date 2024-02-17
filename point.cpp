#include "point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

bool Point::isValid(){
    if (std::isnan(x) || std::isnan(y) || std::isinf(x) ||std::isinf(x)){
        return false;
    }
    return true;
}

QPointF Point::toQPointF(){
    return QPointF(x, y);
}

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

void Point::setX(double x){
    this->x = x;
}

void Point::setY(double y){
    this->y = y;
}


