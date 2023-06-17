#ifndef POINT3D_H
#define POINT3D_H

#include <vector>
#include "interpolate.h" 

class Point3D {
private:
    double E;
    double R, h;
    double Distance;
    bool isInCyllinder;
	double freePathLength;
	double cosTheta;
	double comptonEnergyDifference;
	double FWHM;	

    std::vector<double> position; // Vector for position (px, py, pz)
    std::vector<double> direction; // Vector for direction (dx, dy, dz)
    std::vector<double> crossSections;
	std::vector<std::vector<double>> crossSectionsData;
	Interpolate interpolator;
	std::vector<double> intersection;
	

public:
    Point3D(const std::vector<double>& pos, double Energy, double Radius, double height, double fwhm, const std::vector<std::vector<double>>& cSData);

    void distanceFromOrigin();
    void initializeDirection();
	
    void printAll() const;
    void checkisInCyllinder();
    void updateCrossSections();

    std::vector<double> getPosition() const;
    void setPosition(const std::vector<double>& pos);
    std::vector<double> getDirection() const;
    void setDirection(const std::vector<double>& dir);
	void setEnergy(double En);
	double getEnergy() const;

	void calculateIntersection();

	void generateFreePathLength();

	~Point3D();

	void initializeKahnDirection();
	void calculateEnergyAfterComptonScattering();
	void addFWHMToEnergy();
};

#endif

