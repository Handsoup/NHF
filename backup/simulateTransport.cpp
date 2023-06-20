#include "point3d.h"
#include "energies.h"
#include <cstdlib> 
#include <ctime>
#include <string>
#include <vector>
#include "crossSections.h"
#include "iostream"

void simulateTransport(std::vector<double>& pos, double E, double R, double h, double fwhm, std::vector<std::vector<double>>& cSData, double rho, double numberOfParticles, std::string csvFilePath, Energies& energies) {
	

  	// Setup cross sections
  	processCrossSections(rho, csvFilePath, cSData);


	// Simulation for the life of particles
	
	for(double i=0; i < numberOfParticles; i++) {
		
		std::cout << "particle number: " << i << std::endl;
		Point3D gammaPhoton(pos, E, R, h, fwhm, cSData);
		energies.addToTotalEnergy(gammaPhoton.getEnergy());
		gammaPhoton.calculateIntersection();
		gammaPhoton.checkisInCyllinder();
		if(gammaPhoton.getIntersectionMember(0) == 2){
			
			//std::cout << "there is intersection" << std::endl;			
			gammaPhoton.setPosition({gammaPhoton.getIntersectionMember(1), gammaPhoton.getIntersectionMember(2), gammaPhoton.getIntersectionMember(3)});
			gammaPhoton.generateFreePathLength();
			bool absorption = false;
			gammaPhoton.updateCrossSections();
			//gammaPhoton.printAll();
			for(int j=0; j<gammaPhoton.getPosition().size(); j++) {
			
				gammaPhoton.setIndexedPosition(i, gammaPhoton.getIndexedPosition(i)+gammaPhoton.getIndexedDirection(i)*gammaPhoton.getFreePathLength());

			} 
			energies.addToEnergyInCylinder(gammaPhoton.getEnergy());

			//gammaPhoton.printAll();
			//std::cout << "eddig jó check" << std::endl;
			while(gammaPhoton.getIsInCyllinder() && !absorption){
			
				int r = gammaPhoton.generateRandomEvent();
				
				// Photo-effect
				if(r == 1) {
					
					std::cout << "photo-effect" << std::endl;	
					energies.addToEnergyReleased(gammaPhoton.getEnergy()+gammaPhoton.getFWHMToEnergy(),i);
					absorption = true;
				}
				
				// Compton scattering
				else if(r == 2) {
					std::cout << "compton scattering" << std::endl;	
					gammaPhoton.initializeKahnDirection();
					gammaPhoton.calculateEnergyAfterComptonScattering();
					energies.addToEnergyReleased(gammaPhoton.getComptonEnergyDifference()+gammaPhoton.getFWHMToEnergy(),i);
					std::cout << "a" << std::endl;
					gammaPhoton.updateCrossSections();
					std::cout << "b" << std::endl;
					gammaPhoton.generateFreePathLength();
					for(int j=0; j<gammaPhoton.getPosition().size(); j++) {
			
					gammaPhoton.setIndexedPosition(j, gammaPhoton.getIndexedPosition(j)+gammaPhoton.getIndexedDirection(j)*gammaPhoton.getFreePathLength());
					
					} 
				
				}
				
				// Pair production
				else if(r == 3) {
					std::cout << "pair production start" << std::endl;
					gammaPhoton.initializeDirection();
					energies.addToEnergyReleased(gammaPhoton.getEnergy()-1.022+gammaPhoton.getFWHMToEnergy(),i);
					gammaPhoton.setEnergy(0.522);
					gammaPhoton.updateCrossSections();
					gammaPhoton.savePosition();
					gammaPhoton.saveNegativeDirection();
					bool abs1 = false;
					bool abs2 = false;

					// Photon No.1
					
					gammaPhoton.generateFreePathLength();
					for(int k=0; k<gammaPhoton.getPosition().size(); k++) {
			
						gammaPhoton.setIndexedPosition(k, gammaPhoton.getIndexedPosition(k)+gammaPhoton.getIndexedDirection(k)*gammaPhoton.getFreePathLength());

					}



					while(gammaPhoton.getIsInCyllinder() && !abs1) {
						
						int r1 = 0;

						while(r1 != 1 && r1 != 2) {
						
							r1 = gammaPhoton.generateRandomEvent();
						}

						// Photo-effect
						if(r1 == 1) {

							std::cout << "photon 1, photo-effect" << std::endl;
						
							energies.addToEnergyReleased(gammaPhoton.getEnergy()+gammaPhoton.getFWHMToEnergy(),i);
							abs1 = true;
							
						}

						// Compton scattering

						else {

							std::cout << "photon 1, compton" << std::endl;
						
							gammaPhoton.initializeKahnDirection();
							gammaPhoton.calculateEnergyAfterComptonScattering();
							energies.addToEnergyReleased(gammaPhoton.getComptonEnergyDifference()+gammaPhoton.getFWHMToEnergy(),i);
							gammaPhoton.updateCrossSections();
							gammaPhoton.generateFreePathLength();
							for(int l=0; l<gammaPhoton.getPosition().size(); l++) {

								gammaPhoton.setIndexedPosition(i, gammaPhoton.getIndexedPosition(i)+gammaPhoton.getIndexedDirection(i)*gammaPhoton.getFreePathLength());

							}
							
						}
						
					}
					
					gammaPhoton.loadPosition();
					gammaPhoton.setEnergy(0.511);
					gammaPhoton.updateCrossSections();

					// Photon No. 2

					std::cout << "photon 2" << std::endl;

					gammaPhoton.generateFreePathLength();
					for(int m=0; m<gammaPhoton.getPosition().size(); m++) {
			
						gammaPhoton.setIndexedPosition(m, gammaPhoton.getIndexedPosition(m)+gammaPhoton.getIndexedNegativeDirection(m)*gammaPhoton.getFreePathLength());

					}

					while(gammaPhoton.getIsInCyllinder() && !abs2) {
						
						int r2 = 0;

						while(r2 != 1 && r2 != 2) {
						
							r2 = gammaPhoton.generateRandomEvent();
						}

						// Photo-effect
						if(r2 == 1) {
							
							std::cout << "photon 2, photo-effect" << std::endl;	
							energies.addToEnergyReleased(gammaPhoton.getEnergy()+gammaPhoton.getFWHMToEnergy(),i);
							abs2 = true;
							
						}

						// Compton scattering

						else {
							
							std::cout << "photon 2, compton scattering" << std::endl;	
							gammaPhoton.initializeKahnDirection();
							gammaPhoton.calculateEnergyAfterComptonScattering();
							energies.addToEnergyReleased(gammaPhoton.getComptonEnergyDifference()+gammaPhoton.getFWHMToEnergy(),i);
							gammaPhoton.updateCrossSections();
							gammaPhoton.generateFreePathLength();
							for(int n=0; n<gammaPhoton.getPosition().size(); n++) {

								gammaPhoton.setIndexedPosition(i, gammaPhoton.getIndexedPosition(i)+gammaPhoton.getIndexedDirection(i)*gammaPhoton.getFreePathLength());

							}
							
						}

					}
	
					absorption = true;

				}
				gammaPhoton.checkisInCyllinder();
			
			} 

			//std::cout << "eddig jó, ciklus vége" << std::endl;
		
		}

	}
	std::cout << "max energy: " << energies.getReleasedEnergyMax() << std::endl; 
	energies.calculateEtaTot();
	energies.calculateEtaInt();
	std::cout << "Eta_tot = " << energies.getEtaTot() << std::endl;
	std::cout << "Eta_int = " << energies.getEtaInt() << std::endl;


}

