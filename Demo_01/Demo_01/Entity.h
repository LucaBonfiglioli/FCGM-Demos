#pragma once
#include <cmath>
#include "2DVec.h"

class Entity
{
private:
	float mass;
	float gmass;
	vec pos;
	vec vel;
	float radius;
public:
	Entity(float mass, float gmass, vec pos, vec vel, float radius);
	virtual float getMass() const; 
	virtual void setMass(float value);
	virtual float getGmass() const;
	virtual void setGmass(float value);
	virtual vec getPos() const;
	virtual void setPos(vec pos);
	virtual vec getVel() const;
	virtual void setVel(vec vel);
	virtual float getRadius();
	virtual void setRadius(float value);
	virtual void move(vec force, float time);
	virtual vec getAccelerationAt(vec pos) const;
	virtual vec getForceAt(Entity * e) const;
	~Entity();
};