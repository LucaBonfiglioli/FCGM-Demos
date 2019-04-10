#pragma once
#include "Entity.h"
class Player :
	public Entity
{
private:
	float fuel;
public:
	Player(float mass, float gmass, vec pos, vec vel, float radius, color4f color);
	virtual float getFuel();
	virtual void setFuel(float value);
	virtual void consumeFuel(float time);
	virtual void refillFuel(float time);
	~Player();
};

