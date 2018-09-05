#include "geneticalgorithm.h"

void GeneticAlgorithm::createGenePool(std::vector<Rocket>& rockets)
{
	genePool.clear();
	double maxfit = 0;

	for (int i = 0; i < (int)rockets.size(); i++)
	{
		if (rockets[i].getFitness() > maxfit)
		{
			maxfit = rockets[i].getFitness();
		}
	}

	for (int i = 0; i < (int)rockets.size(); i++)
	{
		rockets[i].setFitness(rockets[i].getFitness() / maxfit);
	}
	
	for (int i = 0; i < (int)rockets.size(); i++)
	{
		int n = (int)(rockets[i].getFitness() * 100);
		for (int j = 0; j < n; j++)
		{
			genePool.push_back(rockets[i].getDna());
		}
	}
}

std::vector<sf::Vector2f> GeneticAlgorithm::evolve()
{
	std::vector<sf::Vector2f> parentA, parentB, child;

	parentA = genePool[rand() % genePool.size()];
	parentB = genePool[rand() % genePool.size()];

	for (int i = 0; i < (int)parentA.size(); i++)
	{
		int mid = rand() % genePool.size();
		if (i < mid)
		{
			child.push_back(parentA[i]);
		}

		else
		{
			child.push_back(parentB[i]);
		}
		
	}

	return child;
}
