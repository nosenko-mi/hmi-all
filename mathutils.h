#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "point.h"

#include <vector>
#include <map>
#include <QPointF>

using std::vector;
using std::map;

class MathUtils
{
public:
    static double calculateF1(double x);
    static double calculateF2(double x);
    static vector<double> calculateRangeF1(double left, double right, int n);
    static vector<double> calculateRangeF2(double left, double right, int n);
    static map<double, double> calculateRange(double left, double right, int n, double (*func)(double));
    static vector<QPointF> calculateRangeToQPoints(double left, double right, int n, double (*func)(double));
    static QVector<Point> calculateRangeToPoints(double left, double right, int n, double (*func)(double));

    static vector<QPointF> scale(map<double, double>, double, double);
    static QVector<Point> scale(QVector<Point>, double, double);
    static QVector<Point> scaleY(QVector<Point> coordinates, double min, double max);

    static double getMinY(QVector<Point>);

private:
    MathUtils();
};

#endif // MATHUTILS_H
