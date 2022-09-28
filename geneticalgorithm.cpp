#include "geneticalgorithm.h"

void GeneticAlgorithm::createGenePool(std::vector<Rocket> &rockets)
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

std::vector<sf::Vector2f> GeneticAlgorithm::evolve(float mutationRate)
{
	std::vector<sf::Vector2f> parentA, parentB, child;

	parentA = genePool[rand() % genePool.size()];
	parentB = genePool[rand() % genePool.size()];

	sf::Vector2f gene;

	for (int i = 0; i < (int)parentA.size(); i++)
	{
		if ((float)(rand() % 101) < (mutationRate / genePool.size()))
		{
			gene = sf::Vector2f((float)(rand() % 3 - 1), (float)(rand() % 3 - 1));
		}
		else if (i < rand() % genePool.size())
		{
			gene = parentA[i];
		}
		else
		{
			gene = parentB[i];
		}

		child.push_back(gene);
	}

	return child;
}
