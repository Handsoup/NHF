#include "point3d.h"
#include "energies.h"
#include <cstdlib> 
#include <ctime>
#include <string>
#include <vector>
#include "crossSections.h"
#include "iostream"

void simulateTransport(std::vector<double>& pos, double E, double R, double h, double fwhm, std::vector<std::vector<double>>& cSData, double rho, double numberOfParticles, std::string csvFilePath, Energies energies) {

	/*
 	// Setup
  	
  	numberOfParticles = 1e5;
  	csvFilePath = "crossSections.csv";
  	std::vector<std::vector<double>> data;
	*/
  
  	// Setup cross sections
  	processCrossSections(rho, csvFilePath, cSData);


	// Simulation loop
	
	for(double i=0; i < numberOfParticles; i++) {
	
		Point3D gammaPhoton(pos, E, R, h, fwhm, cSData);
		gammaPhoton.calculateIntersection();
		gammaPhoton.checkisInCyllinder();

		if(gammaPhoton.getIntersectionMember(0) == 2){

			gammaPhoton.setPosition({gammaPhoton.getIntersectionMember(1), gammaPhoton.getIntersectionMember(2), gammaPhoton.getIntersectionMember(3)});
			gammaPhoton.generateFreePathLength();
			bool absorption = false;
			// position = position + direction * freepathlenth
			std::cout << "eddig jó" << std::endl;
			while(gammaPhoton.getIsInCyllinder() && absorption){
			
				std::cout << "a " << std::endl;	
				

			
			} 

			std::cout << "eddig jó, ciklus vége" << std::endl;
		

		
		}


	}

}

