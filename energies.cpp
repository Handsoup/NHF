#include "energies.h"
#include <iostream>

Energies::Energies() : totalEnergy(0.0), energyInCylinder(0.0), energyReleased(0.0) {}

void Energies::addToTotalEnergy(double value) {
    totalEnergy += value;
}

void Energies::addToEnergyInCylinder(double value) {
    energyInCylinder += value;
}

void Energies::addToEnergyReleased(double value) {
    energyReleased += value;
}

void Energies::setTotalEnergy(double value) {
    totalEnergy = value;
}

void Energies::setEnergyInCylinder(double value) {
    energyInCylinder = value;
}

void Energies::setEnergyReleased(double value) {
    energyReleased = value;
}

double Energies::getTotalEnergy() const {
    return totalEnergy;
}

double Energies::getEnergyInCylinder() const {
    return energyInCylinder;
}

double Energies::getEnergyReleased() const {
    return energyReleased;
}

void Energies::printAll() const {
    std::cout << "Total Energy: " << totalEnergy << std::endl;
    std::cout << "Energy in Cylinder: " << energyInCylinder << std::endl;
    std::cout << "Energy Released: " << energyReleased << std::endl;
}

