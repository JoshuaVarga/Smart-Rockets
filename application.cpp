/**
rocket.cpp
Purpose: Core of the program.

@author Joshua Varga
@version 1.0
*/

#include "application.h"

Application::Application(int w, int h, int s, int p, float m)
{
	width = w;
	height = h;
	stepLimit = s;
	populationSize = p;
	mutationRate = m;

	window.create(sf::VideoMode(width, height), "Smart Rockets",
				  sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	// Random seed.
	srand((unsigned int)time(NULL));

	// Rocket
	rocketTexture.loadFromFile("assets/rocket.png");

	// Asteroid.
	asteroidTexture.loadFromFile("assets/asteroid.png");
	asteroid.setTexture(asteroidTexture);
	asteroid.setPosition(224, 64);

	// Earth.
	earthTexture.loadFromFile("assets/earth.png");
	earth.setTexture(earthTexture);
	earth.setPosition(176, 128);
	earth.setScale(8, 8);

	rockets.resize(populationSize);

	for (int i = 0; i < populationSize; i++)
	{
		Rocket rocket(stepLimit, rocketTexture);
		rockets[i] = rocket;
	}
}

void Application::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case (sf::Event::Closed):
		{
			window.close();
		}
		}
	}
}

void Application::run()
{
	while (window.isOpen())
	{
		if (step < stepLimit)
		{
			step++;
		}

		else
		{
			step = 0;

			geneticAlgorithm.createGenePool(rockets);
			double avg = 0;
			for (int i = 0; i < (int)rockets.size(); i++)
			{
				avg += rockets[i].getFitness();
			}
			std::cout << "avg: " << avg / rockets.size() << std::endl;
			for (int i = 0; i < (int)rockets.size(); i++)
			{
				Rocket rocket(geneticAlgorithm.evolve(mutationRate), rocketTexture);
				// Rocket rocket(stepLimit, rocketTexture);
				rockets[i] = rocket;
			}
		}

		pollEvents();

		window.clear();

		for (int i = 0; i < populationSize; i++)
		{
			rockets[i].calculateFitness(asteroid);
			if (step < stepLimit)
			{
				rockets[i].update(step);
			}
			rockets[i].collision(earth, asteroid);
			window.draw(rockets[i]);
		}

		window.draw(earth);
		window.draw(asteroid);

		window.display();
	}
}
