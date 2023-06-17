#include "point3d.h"
#include "random_addition.h"
#include "energies.h"
#include <cstdlib> 
#include <ctime>

void simulateTransport(std::vector<double> pos, double E, double R, double h, double fwhm, std::vector<std::vector<double>> cSData, double rho, double numberOfParticles, std::string csvFilePath) {

 	// Setup
  	
  	double numberOfParticles = 1e5;
  	std::string csvFilePath = "crossSections.csv";
  	std::vector<std::vector<double>> data;
	
  
  	// Setup cross sections
  	processCrossSections(rho, csvFilePath, data);

  	Point3D photon(r, Energy, R, h, FWHM, data);	

	Energies energies;	

	// Simulation loop

}

