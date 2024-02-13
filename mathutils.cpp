#include "mathutils.h"
#include "cmath"

MathUtils::MathUtils() {}

/**
 * Result of (x^2-x-1)^x^2-1
 *
 * @param x
 * @return y
 */
double MathUtils::calulateF1(double x){
    double e = pow(x, 2) - 1;
    return pow((pow(x, 2) - x - 1), e);
}

/**
 * Result of (cos2x + 5 singx + 3)^3
 *
 * @param x Angle in radians.
 * @return y
 */
double MathUtils::calulateF2(double x){
    double c = 1 - 2 * pow(sin(x), 2);
    return pow((c + 5 * sin(x) +3), 3);
}
