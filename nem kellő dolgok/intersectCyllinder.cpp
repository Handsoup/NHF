#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> intersectCylinder(const double radius, const double height, const std::vector<double>& linePoint, const std::vector<double>& lineDirection) {
    std::vector<double> intersection(4, 0); // Initialize the result vector with all elements as 0

    // Calculate coefficients for the quadratic equation
    double a = lineDirection[0] * lineDirection[0] + lineDirection[1] * lineDirection[1];
    double b = 2 * (linePoint[0] * lineDirection[0] + linePoint[1] * lineDirection[1]);
    double c = linePoint[0] * linePoint[0] + linePoint[1] * linePoint[1] - radius * radius;

    // Calculate the discriminant
    double discriminant = b * b - 4 * a * c;

    // No intersection if discriminant is negative
    if (discriminant < 0) {
        return intersection; // Return the vector containing four zeros
    }
    // One intersection if discriminant is zero
    else if (discriminant == 0) {
        double t = -b / (2 * a);
        double z = linePoint[2] + t * lineDirection[2];

        // Check if the intersection point lies within the height range of the cylinder and in front of the line point
        if (z >= -height / 2 && z <= height / 2 && t >= 0) {
            // Check if the intersection point is in the direction of the line
            std::vector<double> intersectionPoint = {linePoint[0] + t * lineDirection[0], linePoint[1] + t * lineDirection[1], z};
            std::vector<double> direction = {lineDirection[0], lineDirection[1], lineDirection[2]};
            double dotProduct = direction[0] * (intersectionPoint[0] - linePoint[0]) + direction[1] * (intersectionPoint[1] - linePoint[1]) + direction[2] * (intersectionPoint[2] - linePoint[2]);

            if (dotProduct >= 0) {
                intersection[0] = 1; // One intersection
                intersection[1] = intersectionPoint[0];
                intersection[2] = intersectionPoint[1];
                intersection[3] = intersectionPoint[2];
            }
        }
    }
    // Two intersections if discriminant is positive
    else {
        double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b - std::sqrt(discriminant)) / (2 * a);
        double z1 = linePoint[2] + t1 * lineDirection[2];
        double z2 = linePoint[2] + t2 * lineDirection[2];

        // Check if the intersection points lie within the height range of the cylinder and in front of the line point
        bool isIntersection1InRange = (z1 >= -height / 2 && z1 <= height / 2 && t1 >= 0);
        bool isIntersection2InRange = (z2 >= -height / 2 && z2 <= height / 2 && t2 >= 0);

        if (isIntersection1InRange && isIntersection2InRange) {
            // Both intersections are in range, check if they are in the direction of the line
            std::vector<double> intersectionPoint1 = {linePoint[0] + t1 * lineDirection[0], linePoint[1] + t1 * lineDirection[1], z1};
            std::vector<double> intersectionPoint2 = {linePoint[0] + t2 * lineDirection[0], linePoint[1] + t2 * lineDirection[1], z2};
            std::vector<double> direction = {lineDirection[0], lineDirection[1], lineDirection[2]};
            double dotProduct1 = direction[0] * (intersectionPoint1[0] - linePoint[0]) + direction[1] * (intersectionPoint1[1] - linePoint[1]) + direction[2] * (intersectionPoint1[2] - linePoint[2]);
            double dotProduct2 = direction[0] * (intersectionPoint2[0] - linePoint[0]) + direction[1] * (intersectionPoint2[1] - linePoint[1]) + direction[2] * (intersectionPoint2[2] - linePoint[2]);

            if (dotProduct1 >= 0 && dotProduct2 >= 0) {
                // Both intersection points are in the direction of the line, choose the closest one to the line point
                double dist1 = std::sqrt(std::pow(linePoint[0] + t1 * lineDirection[0], 2) + std::pow(linePoint[1] + t1 * lineDirection[1], 2) + std::pow(z1 - linePoint[2], 2));
                double dist2 = std::sqrt(std::pow(linePoint[0] + t2 * lineDirection[0], 2) + std::pow(linePoint[1] + t2 * lineDirection[1], 2) + std::pow(z2 - linePoint[2], 2));

                intersection[0] = 2; // Two intersections

                if (dist1 <= dist2) {
                    intersection[1] = intersectionPoint1[0];
                    intersection[2] = intersectionPoint1[1];
                    intersection[3] = intersectionPoint1[2];
                } else {
                    intersection[1] = intersectionPoint2[0];
                    intersection[2] = intersectionPoint2[1];
                    intersection[3] = intersectionPoint2[2];
                }
            } else if (dotProduct1 >= 0) {
                intersection[0] = 1; // One intersection
                intersection[1] = intersectionPoint1[0];
                intersection[2] = intersectionPoint1[1];
                intersection[3] = intersectionPoint1[2];
            } else if (dotProduct2 >= 0) {
                intersection[0] = 1; // One intersection
                intersection[1] = intersectionPoint2[0];
                intersection[2] = intersectionPoint2[1];
                intersection[3] = intersectionPoint2[2];
            }
        } else if (isIntersection1InRange) {
            // Only the first intersection is in range, check if it is in the direction of the line
            std::vector<double> intersectionPoint1 = {linePoint[0] + t1 * lineDirection[0], linePoint[1] + t1 * lineDirection[1], z1};
            std::vector<double> direction = {lineDirection[0], lineDirection[1], lineDirection[2]};
            double dotProduct1 = direction[0] * (intersectionPoint1[0] - linePoint[0]) + direction[1] * (intersectionPoint1[1] - linePoint[1]) + direction[2] * (intersectionPoint1[2] - linePoint[2]);

            if (dotProduct1 >= 0) {
                intersection[0] = 1; // One intersection
                intersection[1] = intersectionPoint1[0];
                intersection[2] = intersectionPoint1[1];
                intersection[3] = intersectionPoint1[2];
            }
        } else if (isIntersection2InRange) {
            // Only the second intersection is in range, check if it is in the direction of the line
            std::vector<double> intersectionPoint2 = {linePoint[0] + t2 * lineDirection[0], linePoint[1] + t2 * lineDirection[1], z2};
            std::vector<double> direction = {lineDirection[0], lineDirection[1], lineDirection[2]};
            double dotProduct2 = direction[0] * (intersectionPoint2[0] - linePoint[0]) + direction[1] * (intersectionPoint2[1] - linePoint[1]) + direction[2] * (intersectionPoint2[2] - linePoint[2]);

            if (dotProduct2 >= 0) {
                intersection[0] = 1; // One intersection
                intersection[1] = intersectionPoint2[0];
                intersection[2] = intersectionPoint2[1];
                intersection[3] = intersectionPoint2[2];
            }
        }
    }

    return intersection;
}

int main() {
    // Example usage
    std::vector<double> linePoint = {0.0, sqrt(2.0), 0.0};
    std::vector<double> lineDirection = {-1.0, -1.0, 0.0};
    double radius = 2.0;
    double height = 4.0;

    std::vector<double> result = intersectCylinder(radius, height, linePoint, lineDirection);

    if (result[0] == 0) {
        std::cout << "No intersections" << std::endl;
    } else if (result[0] == 1) {
        std::cout << "One intersection: (" << result[1] << ", " << result[2] << ", " << result[3] << ")" << std::endl;
    } else if (result[0] == 2) {
        std::cout << "Two intersections" << std::endl;
        std::cout << "Intersection 1: (" << result[1] << ", " << result[2] << ", " << result[3] << ")" << std::endl;
        std::cout << "Intersection 2: (" << result[1] << ", " << result[2] << ", " << -result[3] << ")" << std::endl;
    }

    return 0;
}

