/**
	rocket.cpp
	Purpose: Rocket capable of learning through genetic algorithms.

	@author Joshua Varga
	@version 1.0
*/

#include "rocket.h"

double Rocket::heading(sf::Vector2f vector)
{
	return (180 / M_PI) * atan2 (vector.y, vector.x);
}

double Rocket::map(double x, double in_min, double in_max, double out_min, double out_max)
{
	double slope = 1.0 * (out_max - out_min) / (in_max - in_min);
	return out_min + slope * (x - in_min);
}

void Rocket::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Rocket::Rocket(int stepLimit, sf::Texture& texture)
{
	position = sf::Vector2f(240, 624);
	velocity = sf::Vector2f(0, 0);

	sprite.setTexture(texture);
	sprite.setPosition(position);

	for (int i = 0; i < stepLimit; i++)
	{
		dna.push_back(sf::Vector2f((float)(rand() % 3 - 1), (float)(rand() % 3 - 1)));
	}
}

Rocket::Rocket(std::vector<sf::Vector2f> newDna, sf::Texture & texture)
{
	position = sf::Vector2f(240, 624);
	velocity = sf::Vector2f(0, 0);

	sprite.setTexture(texture);
	sprite.setPosition(position);

	dna = newDna;
}

void Rocket::applyForce(sf::Vector2f force)
{
	acceleration += force;
}

void Rocket::collision(sf::Sprite earth, sf::Sprite asteroid)
{
	if (position.x < 0 || position.x > 480 || position.y < 0 || position.y > 640)
	{
		fitness -= 200;
		crashed = true;
	}
	
	if (earth.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		fitness -= 200;
		crashed = true;
	}

	if (asteroid.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		position = asteroid.getPosition();
		sprite.setPosition(position);
		fitness += 200;
		crashed = true;
	}

	if (fitness < 0)
	{
		fitness = 0;
	}
}

void Rocket::calculateFitness(sf::Sprite asteroid)
{
	float distance = sqrt(pow((asteroid.getPosition().x - position.x), 2) +
		pow((asteroid.getPosition().y - position.y), 2));

	fitness = map(distance, 0, 640, 640, 0);
}

double Rocket::getFitness()
{
	return fitness;
}

void Rocket::setFitness(double newFitness)
{
	fitness = newFitness;
}

std::vector<sf::Vector2f> Rocket::getDna()
{
	return dna;
}

void Rocket::update(int step)
{
	if (!crashed)
	{
		applyForce(dna[step]);
		velocity += acceleration;
		position += velocity;
		acceleration = sf::Vector2f(0, 0);

		sprite.setPosition(position);
		sprite.setRotation((float)(heading(velocity) + 90));
	}
}
