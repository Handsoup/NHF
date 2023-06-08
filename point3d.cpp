#include "point3d.h"
#include <cmath>
#include <iostream>
#include <random>

Point3D::Point3D(const std::vector<double>& pos, double Energy, double Radius, double height)
    : E(Energy), R(Radius), h(height), RS(std::sqrt((h/2)*(h/2)+R*R)), Distance(0), position(pos) {
    initializeDirection();
    checkIsSphereInDirection();
	checkisInCyllinder();
}

void Point3D::distanceFromOrigin() {
    Distance = std::sqrt(position[0] * position[0] + position[1] * position[1] + position[2] * position[2]);
}

void Point3D::initializeDirection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    direction = { dis(gen), dis(gen), dis(gen) };
}

void Point3D::printAll() const {
    std::cout << "Position (px, py, pz): " << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
    std::cout << "Direction (dx, dy, dz): " << direction[0] << ", " << direction[1] << ", " << direction[2] << std::endl;
    std::cout << "E: " << E << std::endl;
    std::cout << "isSphereInDirection: " << (isSphereInDirection ? "true" : "false") << std::endl;
	std::cout << "Sphere radius RS:" << RS << std::endl;
  	std::cout << "isInCyllinder: " << (isInCyllinder ? "true" : "false") << std::endl; 	
}


void Point3D::checkIsSphereInDirection() {
	// {{{
    distanceFromOrigin();

    if (Distance < RS) {
        isSphereInDirection = true;
    } else if (std::signbit(position[0]) == std::signbit(direction[0]) ||
               std::signbit(position[1]) == std::signbit(direction[1]) ||
               std::signbit(position[2]) == std::signbit(direction[2])) {
        isSphereInDirection = false;
    } else {
        int l = 0;
        if (std::signbit(position[0]) == -std::signbit(direction[0])) {
            l = 0;
        } else if (std::signbit(position[1]) == -std::signbit(direction[1])) {
            l = 1;
        } else if (std::signbit(position[2]) == -std::signbit(direction[2])) {
            l = 2;
        }
        double n = -position[l] / direction[l];

        std::vector<double> newPosition = position;
        for (size_t i = 0; i < newPosition.size(); i++) {
            newPosition[i] += n * direction[i];
        }
        
        double newDistance = std::sqrt(newPosition[0] * newPosition[0] + newPosition[1] * newPosition[1] + newPosition[2] * newPosition[2]);
        
        if (newDistance <= RS) {
            isSphereInDirection = true;
        } else {
            isSphereInDirection = false;
        }
    }
//}}}
}

void Point3D::checkisInCyllinder() {
	if (position[0] <= R && position[0] >= -R && position[1] <= R && position[1] >= -R && position[2] <= h/2 && position[2] >= -h/2){
	isInCyllinder = true;
	}
	else{
		isInCyllinder = false;
	}
}
std::vector<double> Point3D::getPosition() const {
    return position;
}

void Point3D::setPosition(const std::vector<double>& pos) {
    position = pos;
}
 
std::vector<double> Point3D::getDirection() const {
    return direction;
}

void Point3D::setDirection(const std::vector<double>& dir) {
    direction = dir;
}

bool Point3D::getIsSphereInDirection() const {
    return isSphereInDirection;
}

