#include "rocket.h"

float Rocket::heading(sf::Vector2f vector)
{
	return (180 / M_PI) * atan2 (vector.y, vector.x);
}

void Rocket::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Rocket::Rocket()
{
	position = sf::Vector2f(240, 624);
	velocity = sf::Vector2f(0, 0);

	texture.loadFromFile("Assets/rocket.png");

	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Rocket::applyForce(sf::Vector2f force)
{
	acceleration += force;
}

void Rocket::collision(sf::Sprite earth, sf::Sprite asteroid)
{
	if (position.x < 0 || position.x > 480 || position.y < 0 || position.y > 640)
	{
		crashed = true;
	}
	
	if (earth.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		crashed = true;
	}

	if (asteroid.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		position = asteroid.getPosition();
		fitness += 1;
		crashed = true;
	}
}

void Rocket::calculateFitness(sf::Sprite asteroid)
{
	fitness = 1000;

	int x = position.x - asteroid.getPosition().x;
	int y = position.y - asteroid.getPosition().y;

	fitness -= sqrt(pow(x, 2) + pow(y, 2));

	fitness /= 1000;
}

float Rocket::getFitness()
{
	return fitness;
}

void Rocket::init(int stepLimit)
{
	for (int i = 0; i < stepLimit; i++)
	{
		dna.push_back(sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1));
	}
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
		sprite.setRotation(heading(velocity) + 90);
	}
}
