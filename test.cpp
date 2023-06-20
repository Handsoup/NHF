// this will be a test to simulateTransport and ofcourse to main

#include <iostream>
#include <string>
#include <vector>
#include "energies.h"
#include "simulateTransport.h"


int main() {
    std::vector<double> pos={3,-3,2};
    double E = 1.6617;//keV
    double R = 2.5;
    double h = 3;
    double fwhm = 6.0;
    std::vector<std::vector<double>> cSData;
    double rho = 3.67;
    double numberOfParticles = 100000;
    std::string csvFilePath = "crossSections.csv";
    Energies energies(numberOfParticles);

    simulateTransport(pos, E, R, h, fwhm, cSData, rho, numberOfParticles, csvFilePath, energies);


    return 0;
}







