#include <iostream>
#include <random>
#include <cmath>

double addRandomValue(double input, double fwhm) {
    // Calculate the standard deviation based on FWHM
    double sigma = fwhm / (2.0 * std::sqrt(2.0 * std::log(2.0)));
    
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a normal distribution with mean 0 and standard deviation sigma
    std::normal_distribution<> dist(0.0, sigma);
    
    // Generate a random value from the distribution
    double randomValue = dist(gen);
    
    // Add the random value to the input
    double result = input + randomValue;
    
    return result;
}

int main() {
    double inputValue;
    double fwhmValue;
    
    std::cout << "Enter a double value: ";
    std::cin >> inputValue;
    
    std::cout << "Enter the FWHM value: ";
    std::cin >> fwhmValue;
    
    double result = addRandomValue(inputValue, fwhmValue);
    
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}

