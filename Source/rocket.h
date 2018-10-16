/**
rocket.h
Purpose: Rocket capable of learning through genetic algorithms.

@author Joshua Varga
@version 1.0
*/

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

	double fitness;
	std::vector<sf::Vector2f> dna;

	bool crashed = false;

	double round(double d);
	double heading(sf::Vector2f vector);
	double map(double x, double in_min, double in_max, double out_min, double out_max);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;

public:
	Rocket() {};
	Rocket(int stepLimit, sf::Texture& texture);
	Rocket(std::vector<sf::Vector2f> newDna, sf::Texture& texture);

	void applyForce(sf::Vector2f force);
	void collision(sf::Sprite earth, sf::Sprite asteroid);

	void calculateFitness(sf::Sprite asteroid);
	double getFitness();
	void setFitness(double newFitness);
	std::vector<sf::Vector2f> getDna();

	void update(int step);
	
};

#endif // ROCKET_H