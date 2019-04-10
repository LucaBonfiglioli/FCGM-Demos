#include "Player.h"


Player::Player(float mass, float gmass, vec pos, vec vel, float radius, color4f color)
	:Entity(mass, gmass, pos, vel, radius, color)
{
	this->setFuel(1.0f);
}

float Player::getFuel()
{
	return this->fuel;
}

void Player::setFuel(float value)
{
	this->setColor(color4f{ 1.0f - value , value, 0.2f, 1.0f });
	this->setMass(this->getMass() + (value - this->getFuel()) * FUEL_DENSITY);
	this->fuel = value;
}

void Player::consumeFuel(float time)
{
	this->setFuel(this->getFuel() - time * FUEL_CONSUMPTION_RATE);
	if (this->getFuel() < 0)
		this->setFuel(0.0f);
}

void Player::refillFuel(float time)
{
	this->setFuel(this->getFuel() + time * FUEL_REFILL_RATE);
	if (this->getFuel() > 1)
		this->setFuel(1.0f);
}

Player::~Player()
{
}
