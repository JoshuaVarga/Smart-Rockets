#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "rocket.h"

class GeneticAlgorithm
{
private:
	std::vector<std::vector<sf::Vector2f>> genePool;

public:
	void createGenePool(std::vector<Rocket> &rockets);
	std::vector<sf::Vector2f> evolve(float mutationRate);
};

#endif // GENETICALGORITHM_H