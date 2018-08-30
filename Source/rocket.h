#ifndef   ROCKET_H
#define   ROCKET_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include <iostream>

#include <SFML/Graphics.hpp>

class Rocket : public sf::Drawable
{
private:
	sf::Texture texture;
	sf::Sprite  sprite;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	float fitness;
	std::vector<sf::Vector2f> dna;

	bool crashed = false;

	float heading(sf::Vector2f vector);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

public:
	Rocket();

	void applyForce(sf::Vector2f force);
	void collision(sf::Sprite earth, sf::Sprite asteroid);

	void calculateFitness(sf::Sprite asteroid);
	float getFitness();

	void init(int stepLimit);
	void update(int step);
	
};

#endif // ROCKET_H