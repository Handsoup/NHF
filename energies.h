#ifndef ENERGIES_H
#define ENERGIES_H

class Energies {
private:
    double totalEnergy;
    double energyInCylinder;
    double energyReleased;

public:
    Energies();

    void addToTotalEnergy(double value);
    void addToEnergyInCylinder(double value);
    void addToEnergyReleased(double value);

    void setTotalEnergy(double value);
    void setEnergyInCylinder(double value);
    void setEnergyReleased(double value);

    double getTotalEnergy() const;
    double getEnergyInCylinder() const;
    double getEnergyReleased() const;

    void printAll() const;
};

#endif

