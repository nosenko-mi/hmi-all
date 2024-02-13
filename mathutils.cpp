#include "mathutils.h"
#include "cmath"

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

std::map<double, double> MathUtils::calculateRange(double left, double right, int n, double (*func)(double)){
    std::map<double, double> mapRes;
    std::vector<double> result = {};

    double step = (right - left) / n;
    double current = left;
    for(int i = 0; i <= n; i++){
        mapRes[current] = func(current);
        result.push_back(func(current));
        current += step;
    }

    return mapRes;

}


std::vector<double> MathUtils::calculateRangeF1(double left, double right, int n){
    std::vector<double> result = {};
    double step = (right - left) / n;
    double current = left;
    for(int i = 0; i <= n; i++){
        result.push_back(calculateF1(current));
        current += step;
    }

    return result;
    // return calculateRange(left, right, n, &calculateF1);
}
