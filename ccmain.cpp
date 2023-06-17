#include "crossSections.h"
#include "interpolate.h"
#include <iostream>
#include "point3d.h"
#include "energies.h"

int main() {

  // Input parameters
 
  std::vector<double> r = {5.0, 5.0, 5.0};
  double Energy = 10.0;
  double R = 5.0;
  double h = 6.0;	
  double rho = 0.2;
  double FWHM = 0.001;

  // Variables for calculations
  //
  double numberOfParticles = 1e5;
  std::string csvFilePath = "crossSections.csv";
  std::vector<std::vector<double>> data;
	
  
  // Setup cross sections
  processCrossSections(rho, csvFilePath, data);

  Point3D photon(r, Energy, R, h, FWHM, data);
  photon.printAll();
  photon.setEnergy(5.1);
  photon.updateCrossSections();
  photon.generateFreePathLength();
  photon.printAll();

  // Setup Energy container
  Energies energies;









  return 0;
}

