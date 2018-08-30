#ifndef   APPLICATION_H
#define   APPLICATION_H

#include <SFML/Graphics.hpp>

#include "rocket.h"

class Application
{
private:
	int width, height, stepLimit, populationSize, mutationRate;
	int step = 0;

	sf::RenderWindow window;

	sf::Texture asteroidTexture, earthTexture;
	sf::Sprite asteroid, earth;

	std::vector<Rocket> rockets;

public:
	Application(int w, int h, int s, int p, int m);

	void pollEvents();
	void run();
};

#endif // APPLICATION_H
