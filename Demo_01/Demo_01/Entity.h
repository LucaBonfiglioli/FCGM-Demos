#pragma once
#include <cmath>
#include "2DVec.h"
#include "commons.h"

class Entity
{
private:
	float mass;
	float gmass;
	vec pos;
	vec vel;
	float radius;
	color4f color;
public:
	Entity(float mass, float gmass, vec pos, vec vel, float radius, color4f color);
	virtual float getMass() const; 
	virtual void setMass(float value);
	virtual float getGmass() const;
	virtual void setGmass(float value);
	virtual vec getPos() const;
	virtual void setPos(vec pos);
	virtual vec getVel() const;
	virtual void setVel(vec vel);
	virtual float getRadius() const;
	virtual void setRadius(float value);
	virtual color4f getColor() const;
	virtual void setColor(color4f color);
	virtual void move(vec force, float time);
	virtual vec getAccelerationAt(vec pos) const;
	virtual vec getForceAt(Entity * e) const;
	static bool areColliding(Entity * e1, Entity * e2);
	static void handleCollision(Entity * e1, Entity * e2);
	~Entity();
};