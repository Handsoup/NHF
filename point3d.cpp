#include "point3d.h"
#include <cmath>
#include <iostream>
#include <random>
#include <algorithm>

//constructor

Point3D::Point3D(const std::vector<double>& pos, double Energy, double Radius, double height, double fwhm, const std::vector<std::vector<double>>& cSData)
    : E(Energy), R(Radius), h(height), Distance(0), position(pos), interpolator(cSData), FWHM(fwhm), crossSections(4, 0.0), intersection(4,0.0), freePathLength(-1), comptonEnergyDifference(-1), negativeDirection(3,0.0), savedPosition(3,0.0) {
    initializeDirection();
	checkisInCyllinder();
	updateCrossSections();
	calculateIntersection();

}

/*
void Point3D::distanceFromOrigin() {
    Distance = std::sqrt(position[0] * position[0] + position[1] * position[1] + position[2] * position[2]);
}*/

void Point3D::initializeDirection() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random generator
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
	
	double lengthSquared;

    do {
        direction = { dis(gen), dis(gen), dis(gen) };
		 lengthSquared = std::sqrt(direction[0]*direction[0]+direction[1]*direction[1]+direction[2]*direction[2]);

    } while (lengthSquared > 1.0);

	double length = std::sqrt(lengthSquared);
	direction[0] /= length;
	direction[1] /= length;
	direction[2] /= length;

}

void Point3D::printAll() const {
    std::cout << "Position (px, py, pz): " << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
    std::cout << "Direction (dx, dy, dz): " << direction[0] << ", " << direction[1] << ", " << direction[2] << std::endl;
    std::cout << "E: " << E << std::endl;
  	std::cout << "isInCyllinder: " << (isInCyllinder ? "true" : "false") << std::endl; 
	std::cout << "cross sections: " << crossSections[0] << ", " << crossSections[1] << ", " << crossSections[2] << ", " << crossSections[3] << std::endl;
	std:: cout << "intersect values: " 	<< intersection[0] << ", " << intersection[1] << ", " << intersection[2] << ", " <<  intersection[3] << ", " << std::endl;
	std::cout << "free path length: " << freePathLength << std::endl;
}

void Point3D::checkisInCyllinder() const {
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

double Point3D::getEnergy() const {
    return E;
}

void Point3D::setEnergy(double En) {
    E = En;
}

void Point3D::updateCrossSections() {

	//splineInterpolation can be exchanged for linearInterpolation(col,E)

	//Compton
	crossSections[0]=interpolator.splineInterpolation(1, E);

	//Photo-effect
	crossSections[1]=interpolator.splineInterpolation(2, E);

	//Pair production
	crossSections[2]=interpolator.splineInterpolation(3, E);

	//Total cross section
	crossSections[3]=interpolator.splineInterpolation(4,E);

}

void Point3D::calculateIntersection()
{


    // Calculate coefficients for the quadratic equation
    double a = direction[0] * direction[0] + direction[1] * direction[1];
    double b = 2 * (position[0] * direction[0] + position[1] * direction[1]);
    double c = position[0] * position[0] + position[1] * position[1] - R * R;

    // Calculate the discriminant
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        // Calculate the two intersection points
        double t1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b - std::sqrt(discriminant)) / (2 * a);

        // Calculate the z coordinates of the intersection points
        double z1 = position[2] + t1 * direction[2];
        double z2 = position[2] + t2 * direction[2];

        // Transform the intersection points to the top or bottom of the cylinder if necessary
        if (z1 < -h / 2)
        {
            double t = (-h / 2 - position[2]) / direction[2];
            z1 = -h / 2;
            t1 = t;
        }
        else if (z1 > h / 2)
        {
            double t = (h / 2 - position[2]) / direction[2];
            z1 = h / 2;
            t1 = t;
        }

        if (z2 < -h / 2)
        {
            double t = (-h / 2 - position[2]) / direction[2];
            z2 = -h / 2;
            t2 = t;
        }
        else if (z2 > h / 2)
        {
            double t = (h / 2 - position[2]) / direction[2];
            z2 = h / 2;
            t2 = t;
        }

        // Calculate the coordinates of the closest intersection point
        double x1 = position[0] + t1 * direction[0];
        double y1 = position[1] + t1 * direction[1];
        z1 = position[2] + t1 * direction[2];

        // Set the values in the intersection vector
        intersection[0] = 2; // Number of intersections
        intersection[1] = x1;
        intersection[2] = y1;
        intersection[3] = z1;
    }
}

// Destructor
Point3D::~Point3D() {

}


void Point3D::generateFreePathLength() {
	
	
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
	double r = dis(gen);
	
	freePathLength = -(1.0 / crossSections[3]) * std::log(r);

}



void Point3D::initializeKahnDirection() {

	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

   	double lambda = 0.511/E; // All calculations are in MeV
	bool loop = true;

	// cos theta = 1 + lambda - lambda*X
	double X,R;
	bool i = false;
	bool j = false;

	while (loop == true) {

		// Generate three random real numbers
    	double r1 = dis(gen);
    	double r2 = dis(gen);
    	double r3 = dis(gen);
	

		if (r1 <= (1 +2/lambda)/(9+2/lambda)) {
	
			R = 1 + 2*r2/lambda;
			if (r3 <= 4*(1/R-1/(R*R))) {
		
				i = true;
		
			}	

		}

		else {

			R = (1+2/lambda)/(1+2*r2/lambda);
			if (r3 <= 0.5*((lambda-R*lambda+1)*(lambda-R*lambda+1)+1/R)) {
			
				j = true;
			}
	
		}
		
		if (i && j) {
		
			X = R;
			loop = false;
		}	

	}
	
	cosTheta = 1 + lambda - lambda * X;

	// Random new direction on cone

	double u = direction[0];
    double v = direction[1];
    double w = direction[2];
	double r = dis(gen);
	double phi = M_PI * r;

    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    double sinPhi = sin(phi);
    double cosPhi = cos(phi);

    double sqrtUV = sqrt(u * u + v * v);
    double sqrtUVInv = 1.0 / sqrtUV;

    std::vector<double> result(3);
    direction[0] = (v * sqrtUVInv * sinTheta * cosPhi) + (u * w * sqrtUVInv * sinTheta * sinPhi) + (u * cosTheta);
    direction[1] = (-u * sqrtUVInv * sinTheta * cosPhi) + (v * w * sqrtUVInv * sinTheta * sinPhi) + (v * cosTheta);
    direction[2] = (-sqrtUV * sinTheta * sinPhi) + (w * cosTheta);

}

void Point3D::calculateEnergyAfterComptonScattering() {
    // Constants
    const double electronMass = 0.511; // Electron mass energy equivalent in MeV

    // Calculate the scattered photon's energy
    double finalEnergy = E / (1 + (E / electronMass * (1 - cosTheta)));

    // Calculate the energy difference (change)
    comptonEnergyDifference = E - finalEnergy;

	E = finalEnergy;

}

double Point3D::getFWHMToEnergy() const {

    // Calculate the standard deviation based on FWHM
    double sigma = FWHM / (2.0 * std::sqrt(2.0 * std::log(2.0)));
    
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a normal distribution with mean 0 and standard deviation sigma
    std::normal_distribution<> dist(0.0, sigma);
    
    // Generate a random value from the distribution
    double randomValue = dist(gen);
    
    // Add the random value to the current Energy
    return randomValue;
    
}

double Point3D:: getIntersectionMember(int index) const {
        
		if (index >= 0 && index < intersection.size()) {
            return intersection[index];
        }

	   	else {
            // Handle index out of range error
            std::cerr << "Error: Index out of range!" << std::endl;

            // You can choose to throw an exception or return a default value here
            // For simplicity, we'll return -1 as an error indicator
            return -1;
        }
    }

bool Point3D::getIsInCyllinder() const {

	this->checkisInCyllinder();
	return isInCyllinder;

}

double Point3D::getFreePathLength() const {

	return freePathLength;

}

double Point3D::getIndexedDirection(int index) const {

	return direction[index];

}

double Point3D::getIndexedPosition(int index) const {

	return position[index];

}

void Point3D::setIndexedPosition(int index, double value) {

	position[index] = value;

}

int Point3D::generateRandomEvent() {
    double totalCrossSection = crossSections[3];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, totalCrossSection);
    double randomNumber = dis(gen);

    if (randomNumber <= crossSections[0]) {
        return 2;
    } else if (randomNumber <= crossSections[0] + crossSections[1]) {
        return 1;
    } else {
        return 3;
    }
}

double Point3D::getComptonEnergyDifference() const {

	return comptonEnergyDifference;

}

void Point3D::saveNegativeDirection() {
    for (size_t i = 0; i < direction.size(); ++i) {
        negativeDirection[i] = direction[i] * -1;
    }
}

double Point3D::getIndexedNegativeDirection(int index) const {

	return negativeDirection[index];

}

void Point3D::savePosition() {
    for (size_t i = 0; i < position.size(); ++i) {
        savedPosition[i] = position[i];
    }
}

void Point3D::loadPosition() {
    for (size_t i = 0; i < savedPosition.size(); ++i) {
        position[i] = savedPosition[i];
    }
}









