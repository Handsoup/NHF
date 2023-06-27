// this will be a test to simulateTransport and ofcourse to main

#include <iostream>
#include <string>
#include <vector>
#include "energies.h"
#include "simulateTransport.h"
#include <unistd.h>

int main() {


   
	const char* filename = "output.txt";

    int result = truncate(filename, 0);
    if (result == 0) {
        std::cout << "File contents deleted." << std::endl;
    } else {
        std::cout << "Unable to delete file contents." << std::endl;
    }



	std::vector<double> pos={4.0,4.0,0.0};
    double E = 4.0;//keV
    double R = 3;
    double h = 5;
    double fwhm = 0.008;
    std::vector<std::vector<double>> cSData;
    double rho = 3.67;
    double numberOfParticles = 10000000;
    std::string csvFilePath = "crossSections.csv";
    Energies energies(numberOfParticles);

    simulateTransport(pos, E, R, h, fwhm, cSData, rho, numberOfParticles, csvFilePath, energies);


    return 0;
}







