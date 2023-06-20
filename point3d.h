#ifndef POINT3D_H
#define POINT3D_H

#include <vector>
#include "interpolate.h" 

class Point3D {
private:
    double E;
    double R, h;
    double Distance;
    mutable bool isInCyllinder;
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
	std::vector<double> negativeDirection;
	std::vector<double> savedPosition;
	

public:
    Point3D(const std::vector<double>& pos, double Energy, double Radius, double height, double fwhm, const std::vector<std::vector<double>>& cSData);

    void distanceFromOrigin();
    void initializeDirection();
	
    void printAll() const;
    void checkisInCyllinder() const;
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
	double  getFWHMToEnergy() const;

	double getIntersectionMember(int index) const;
	bool getIsInCyllinder() const;
	double getFreePathLength() const;

	double getIndexedDirection(int index) const;
	double getIndexedPosition(int index) const;
	void setIndexedPosition(int index, double value);
	
	int generateRandomEvent();

	double getComptonEnergyDifference() const;

	void saveNegativeDirection();
	void savePosition();
	void loadPosition();

	double getIndexedNegativeDirection(int index) const;


};

#endif

