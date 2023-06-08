#include "point3d.h"
#include <iostream>

int main() {
    std::vector<double> initialPosition = {5.0, 5.0, 5.0};
    double initialEnergy = 10.0;
    double initialRadius = 4.0;
    double initialHeight = 2.0;

    Point3D point(initialPosition, initialEnergy, initialRadius, initialHeight);

    // Print initial state
    std::cout << "Initial State:" << std::endl;
    point.printAll();

    // Modify position
    std::vector<double> newPosition = {1.0, 1.0, 1.0};
    point.setPosition(newPosition);

    // Modify direction
    std::vector<double> newDirection = {0.5, -0.3, 0.8};
    point.setDirection(newDirection);

	//Update is in cyllinder
	point.checkisInCyllinder();

    // Print modified state
    std::cout << "Modified State:" << std::endl;
    point.printAll();

    return 0;
}

