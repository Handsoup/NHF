#include "energies.h"
#include <iostream>

Energies::Energies(double size)
    : totalEnergy(0.0), energyInCylinder(0.0), energyReleasedSum(0.0), etaTot(0.0), etaInt(0.0) {
    energyReleased.resize(size, 0.0);
}

void Energies::addToTotalEnergy(double value) {
    totalEnergy += value;
}

void Energies::addToEnergyInCylinder(double value) {
    energyInCylinder += value;
}

void Energies::addToEnergyReleased(double value, double index) {
    if (index >= 0 && index < energyReleased.size()) {
        energyReleased[index] += value;
        energyReleasedSum += value;
    } else {
        std::cout << "Invalid index for Released Energy vector." << std::endl;
    }
}

void Energies::calculateEtaTot() {
    if (totalEnergy != 0.0) {
        etaTot = energyReleasedSum / totalEnergy;
    } else {
        std::cout << "Total Energy is zero. Cannot calculate EtaTot." << std::endl;
    }
}

void Energies::calculateEtaInt() {
    if (energyInCylinder != 0.0) {
        etaInt = energyReleasedSum / energyInCylinder;
    } else {
        std::cout << "Energy in Cylinder is zero. Cannot calculate EtaInt." << std::endl;
    }
}

void Energies::setTotalEnergy(double value) {
    totalEnergy = value;
}

void Energies::setEnergyInCylinder(double value) {
    energyInCylinder = value;
}

void Energies::setReleasedEnergy(double value, double index) {
    if (index >= 0 && index < energyReleased.size()) {
        energyReleased[index] = value;
    } else {
        std::cout << "Invalid index for Released Energy vector." << std::endl;
    }
}

double Energies::getTotalEnergy() const {
    return totalEnergy;
}

double Energies::getEnergyInCylinder() const {
    return energyInCylinder;
}

double Energies::getReleasedEnergy(double index) const {
    if (index >= 0 && index < energyReleased.size()) {
        return energyReleased[index];
    } else {
        std::cout << "Invalid index for Released Energy vector." << std::endl;
        return 0.0;
    }
}

double Energies::getReleasedEnergySum() const {
    return energyReleasedSum;
}

double Energies::getEtaTot() const {
    return etaTot;
}

double Energies::getEtaInt() const {
    return etaInt;
}

void Energies::printAll() const {
    std::cout << "Total Energy: " << totalEnergy << std::endl;
    std::cout << "Energy in Cylinder: " << energyInCylinder << std::endl;
    std::cout << "Released Energy: ";
    for (const auto& energy : energyReleased) {
        std::cout << energy << " ";
    }
    std::cout << std::endl;
    std::cout << "Released Energy Sum: " << energyReleasedSum << std::endl;
    std::cout << "EtaTot: " << etaTot << std::endl;
    std::cout << "EtaInt: " << etaInt << std::endl;
}

double Energies::getReleasedEnergyMax() const {

	double tmp = energyReleased[0];
	
	for(int i=0; i<energyReleased.size(); i++){
	
		if (tmp < energyReleased[i]){
		
			tmp = energyReleased[i];
		}
	}

	return tmp;
}




















