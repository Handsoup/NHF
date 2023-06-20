#ifndef ENERGIES_H
#define ENERGIES_H

#include <vector>

class Energies {
private:
    double totalEnergy;
    double energyInCylinder;
    std::vector<double> energyReleased;
    double energyReleasedSum;
    double etaTot;
    double etaInt;

public:
    Energies(double size);

    void addToTotalEnergy(double value);
    void addToEnergyInCylinder(double value);
    void addToEnergyReleased(double value, double index);
    void calculateEtaTot();
    void calculateEtaInt();

    void setTotalEnergy(double value);
    void setEnergyInCylinder(double value);
    void setReleasedEnergy(double value, double index);

    double getTotalEnergy() const;
    double getEnergyInCylinder() const;
    double getReleasedEnergy(double index) const;
    double getReleasedEnergySum() const;
    double getEtaTot() const;
    double getEtaInt() const;
	
	double getReleasedEnergyMax() const;
    void printAll() const;
};

#endif

