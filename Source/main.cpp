/**
	main.cpp
	Purpose: TODO

	@author Joshua Varga
	@version 1.0
*/

#include "application.h"

int main()
{
	int stepLimit, populationSize, mutationRate;

	std::cout << "Enter a step limit: ";
	std::cin >> stepLimit;

	std::cout << "Enter a population size: ";
	std::cin >> populationSize;

	std::cout << "Enter a mutation rate: ";
	std::cin >> mutationRate;

	Application app(480, 640, stepLimit, populationSize, mutationRate);
	app.run();

	return 0;
}