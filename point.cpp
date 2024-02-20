#include "point.h"

Point::Point()
{
    this->x = 0;
    this->y = 0;
}

bool Point::serialize(std::ofstream& stream) const {
    if (std::isnan(y) || std::isinf(y)){
        stream << x << " " << "?" << std::endl;
        return stream.good();
    }
    stream << x << " " << y << std::endl;
    return stream.good();
}

bool Point::deserialize(std::ifstream& stream, Point& point) {
    stream >> point.x;
    std::string yStr;
    stream >> yStr;
    if (yStr == "?") {
        return false; // Deserialization failed if y is not "?"
        point.y = std::numeric_limits<double>::quiet_NaN(); // Set y to NaN
    } else {
        point.y = std::stod(yStr);
    }
    return stream.good();
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


