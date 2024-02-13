#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <vector>
#include <map>


class MathUtils
{
public:
    static double calculateF1(double x);
    static double calculateF2(double x);
    static std::vector<double> calculateRangeF1(double left, double right, int n);
    static std::vector<double> calculateRangeF2(double left, double right, int n);
    static std::map<double, double> calculateRange(double left, double right, int n, double (*func)(double));

private:
    MathUtils();
};

#endif // MATHUTILS_H
