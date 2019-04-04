#pragma once

#include <cmath>
#include "2Dvec.h"

class Entity
{
private:
	float mass;
	float gmass;
	vec pos;
	vec vel;
public:
	Entity(float mass, float gmass, vec pos, vec vel);
	virtual float getMass();
	virtual void setMass(float value);
	virtual float getGmass();
	virtual void setGmass(float value);
	virtual vec getPos();
	virtual void setPos(vec pos);
	virtual vec getVel();
	virtual void setVel(vec vel);
	virtual void move(vec force, float time);
	virtual vec getAccelerationAt(vec pos);
	//virtual vec getForceAt(Entity * e);
	~Entity();
};
