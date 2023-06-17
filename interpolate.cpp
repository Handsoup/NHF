#include "interpolate.h"
#include <iostream>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

Interpolate::Interpolate(const std::vector<std::vector<double>>& inputData) {
    data = inputData;
    spline = nullptr;
    accel = nullptr;
}

Interpolate::~Interpolate() {
    if (spline != nullptr)
        gsl_spline_free(spline);
    if (accel != nullptr)
        gsl_interp_accel_free(accel);
}

double Interpolate::linearInterpolation(int column, double x) {
    // Check if the provided x value matches an existing x value in the data
    for (const auto& row : data) {
        if (row[0] == x) {
            return row[column];
        }
    }

    // Find the index of the left and right neighboring x values
    int leftIndex = -1;
    int rightIndex = -1;

    for (int i = 0; i < data.size(); i++) {
        if (data[i][0] < x)
            leftIndex = i;
        else if (data[i][0] > x) {
            rightIndex = i;
            break;
        }
    }

    // Perform linear interpolation
    if (leftIndex != -1 && rightIndex != -1) {
        double x0 = data[leftIndex][0];
        double x1 = data[rightIndex][0];
        double y0 = data[leftIndex][column];
        double y1 = data[rightIndex][column];

        // Calculate the interpolated y value
        double interpolatedY = y0 + ((x - x0) * (y1 - y0)) / (x1 - x0);
        return interpolatedY;
    } else {
        std::cout << "Cannot perform interpolation. Provided x value is outside the range of the vector." << std::endl;
        return 0.0; // Return a default value if interpolation cannot be performed
    }
}

double Interpolate::splineInterpolation(int column, double x) {
    // Check if the provided x value matches an existing x value in the data
    for (const auto& row : data) {
        if (row[0] == x) {
            return row[column];
        }
    }

    // Check if x is within the range of the data
    if (x < data.front()[0] || x > data.back()[0]) {
        std::cout << "Cannot perform interpolation. Provided x value is outside the range of the vector." << std::endl;
        return 0.0; // Return a default value if interpolation cannot be performed
    }

    // Prepare data for spline interpolation
    size_t size = data.size();
    std::vector<double> xData(size);
    std::vector<double> yData(size);
    for (size_t i = 0; i < size; ++i) {
        xData[i] = data[i][0];
        yData[i] = data[i][column];
    }

    // Initialize GSL spline and accelerator
    if (spline == nullptr) {
        spline = gsl_spline_alloc(gsl_interp_cspline, size);
        accel = gsl_interp_accel_alloc();
    }

    // Set up the spline
    gsl_spline_init(spline, xData.data(), yData.data(), size);

    // Perform spline interpolation
    double interpolatedY = gsl_spline_eval(spline, x, accel);
    return interpolatedY;
}

