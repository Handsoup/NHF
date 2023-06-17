#ifndef INTERPOLATE2_H
#define INTERPOLATE2_H

#include <vector>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

class Interpolate {
private:
    std::vector<std::vector<double>> data;
    gsl_spline* spline;
    gsl_interp_accel* accel;

public:
    Interpolate(const std::vector<std::vector<double>>& inputData);
    ~Interpolate();
    double linearInterpolation(int column, double x);
    double splineInterpolation(int column, double x); // Updated function name
};

#endif  // INTERPOLATE2_H

