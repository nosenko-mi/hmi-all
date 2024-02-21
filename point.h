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
    Point(QString s);

    bool serialize(std::ofstream& stream) const;

    static bool deserialize(std::ifstream& stream, Point& point);

    QString toString(){
        QString xStr = QString::number(x);
        QString yStr;
        if (std::isnan(y) || std::isinf(y)){
            yStr = "?";
        }
        yStr = QString::number(y);

        xStr.append(" ");
        xStr.append(yStr);
        xStr.append(" ");
        xStr.append("\n");
        return xStr;
    }

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
