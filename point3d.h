#ifndef POINT3D_H
#define POINT3D_H

#include <vector>

class Point3D {
private:
    double E;
    double R, h;
	double RS;
    double Distance;
	double isInCyllinder;
    bool isSphereInDirection;
    std::vector<double> position; // Vector for position (px, py, pz)
    std::vector<double> direction; // Vector for direction (dx, dy, dz)

public:
    Point3D(const std::vector<double>& pos, double Energy, double Radius, double height);

    void distanceFromOrigin();
    void initializeDirection();
    void printAll() const;
    void checkIsSphereInDirection();
	void checkisInCyllinder();

    std::vector<double> getPosition() const;
    void setPosition(const std::vector<double>& pos);
    std::vector<double> getDirection() const;
    void setDirection(const std::vector<double>& dir);
    bool getIsSphereInDirection() const;
};

#endif

