#include "application.h"

Application::Application(int w, int h, int s, int p, int m)
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

	// Asteroid.
	asteroidTexture.loadFromFile("Assets/asteroid.png");
	asteroid.setTexture(asteroidTexture);
	asteroid.setPosition(224, 64);

	// Earth.
	earthTexture.loadFromFile("Assets/earth.png");
	earth.setTexture(earthTexture);
	earth.setPosition(176, 128);
	earth.setScale(8, 8);

	rockets.resize(populationSize);

	for (int i = 0; i < populationSize; i++)
	{
		Rocket rocket;
		rocket.init(stepLimit);
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

			for (int i = 0; i < populationSize; i++)
			{
				Rocket rocket;
				rocket.init(stepLimit);
				rockets[i] = rocket;
			}
		}

		pollEvents();

		window.clear();

		for (int i = 0; i < rockets.size(); i++)
		{
			rockets[i].update(step);
			rockets[i].calculateFitness(asteroid);
			rockets[i].collision(earth, earth);
			window.draw(rockets[i]);
		}

		std::cout << rockets[0].getFitness() << "\n";

		window.draw(earth);
		window.draw(asteroid);

		window.display();
	}
}
