#include "mathutils.h"
#include "cmath"
#include "point.h"
#include <algorithm>
#include <iostream>

MathUtils::MathUtils() {}

/**
 * Result of (x^2-x-1)^x^2-1
 *
 * @param x
 * @return y
 */
double MathUtils::calculateF1(double x){
    double result = 0;
    try {
        double e = pow(x, 2) - 1;
        result = pow((pow(x, 2) - x - 1), e);
    } catch (const std::exception) {

    }
    return result;
}

/**
 * Result of (cos2x + 5 singx + 3)^3
 *
 * @param x Angle in radians.
 * @return y
 */
double MathUtils::calculateF2(double x){
    double c = 1 - 2 * pow(sin(x), 2);
    return pow((c + 5 * sin(x) +3), 3);
}

map<double, double> MathUtils::calculateRange(double left, double right, int n, double (*func)(double)){
    map<double, double> mapRes;
    vector<double> result = {};

    double step = (right - left) / n;
    double current = left;
    for(int i = 0; i <= n; i++){
        mapRes[current] = func(current);
        result.push_back(func(current));
        current += step;
    }

    return mapRes;

}

vector<QPointF> MathUtils::calculateRangeToQPoints(double left, double right, int n, double (*func)(double)){
    vector<QPointF> result;

    double step = (right - left) / n;
    double currentX = left;
    double currentY;
    for(int i = 0; i <= n; i++){
        currentY = func(currentX);
        result.push_back(QPointF(currentX, currentY));
        currentX += step;
    }

    return result;

}

QVector<Point> MathUtils::calculateRangeToPoints(double left, double right, int n, double (*func)(double)){
    QVector<Point> result;

    double step = (right - left) / n;
    double currentX = left;
    double currentY;
    for(int i = 0; i <= n; i++){
        currentY = func(currentX);
        result.append(Point(currentX, currentY));
        currentX += step;
    }

    return result;

}

vector<QPointF> MathUtils::scale(map<double, double> coordinates, double min, double max){

    vector<QPointF> points;
    vector<double> allValues;

    for (const auto&[x, y] : coordinates){

        if(!std::isnan(y) || !std::isinf(y)){
            allValues.push_back(y);
        }
    }

    const auto [localMin, localMax] = std::minmax_element(begin(allValues), end(allValues));
    std::cout << "min = " << *localMin << ", max = " << *localMax << '\n';
    double scaledX, scaledY;
    for (const auto&[x, y] : coordinates){
        scaledX = ((x - *localMin)/(*localMax - *localMin))*(max - min)+min;
        scaledY = ((y - *localMin)/(localMax - localMin))*(max - min)+min;
        points.push_back(QPointF(scaledX, scaledY));
    }

    return points;

}

QVector<Point> MathUtils::scale(QVector<Point> coordinates, double w, double h){

    QVector<Point> points;
    vector<double> allValues;

    double minY = 0;
    double maxY = 0;
    for (auto c : coordinates){
        if(!std::isnan(c.getX()) || !std::isinf(c.getY())){
            allValues.push_back(c.getY());
            if (c.getY() > maxY){
                maxY = c.getY();
            }
            if (c.getY() < minY){
                minY = c.getY();
            }
        }
    }
    // const auto [minY, maxY] = std::minmax_element(begin(allValues), end(allValues));
    allValues.clear();

    for (auto c : coordinates){
        allValues.push_back(c.getX());
    }
    const auto [minX, maxX] = std::minmax_element(begin(allValues), end(allValues));

    double xScale = w / (maxX - minX);
    double yScale = h / (maxY - minY);

    std::cout << "minY = " << minY << ", maxY = " << maxY << '\n';
    std::cout << "minX = " << *minX << ", maxX = " << *maxX << '\n';

    double scaledX, scaledY;

    for (Point& c : coordinates) {
        scaledX = c.getX(); // (c.getX() - *minX) * xScale;
        scaledY = (c.getY() - minY) * yScale;
        points.append(Point(scaledX, scaledY));
    }

    // for (const auto&[x, y] : coordinates){
    //     scaledX = ((x - *localMin)/(*localMax - *localMin))*(max - min)+min;
    //     scaledY = ((y - *localMin)/(localMax - localMin))*(max - min)+min;
    //     points.push_back(QPointF(scaledX, scaledY));
    // }

    return points;

}

// https://stats.stackexchange.com/questions/281162/scale-a-number-between-a-range
QVector<Point> MathUtils::scaleY(QVector<Point> coordinates, double min, double max){
    QVector<Point> points;
    vector<double> allValues;

    double localMin = 0;
    double localMax = 0;
    for (auto c : coordinates){
        if(!std::isnan(c.getX()) || !std::isinf(c.getY())){
            allValues.push_back(c.getY());
            if (c.getY() > localMax){
                localMax = c.getY();
            }
            if (c.getY() < localMin){
                localMin = c.getY();
            }
        }
    }

    double scaledX, scaledY;

    for (Point& c : coordinates) {
        scaledY = (c.getY() - localMin)/(localMax-localMin)*(max-min)+min;
        points.append(Point(c.getX(), scaledY));
    }

    // for (const auto&[x, y] : coordinates){
    //     scaledX = ((x - *localMin)/(*localMax - *localMin))*(max - min)+min;
    //     scaledY = ((y - *localMin)/(localMax - localMin))*(max - min)+min;
    //     points.push_back(QPointF(scaledX, scaledY));
    // }

    return points;
}


vector<double> MathUtils::calculateRangeF1(double left, double right, int n){
    vector<double> result = {};
    double step = (right - left) / n;
    double current = left;
    for(int i = 0; i <= n; i++){
        result.push_back(calculateF1(current));
        current += step;
    }

    return result;
    // return calculateRange(left, right, n, &calculateF1);
}

double MathUtils::getMinY(QVector<Point> points){

    double minY = 0;

    for (auto p : points){
        if(p.isValid()){
            if (p.getY() < minY){
                minY = p.getY();
            }
        }
    }

    return minY;
}
