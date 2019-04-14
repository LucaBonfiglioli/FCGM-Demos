#pragma once
#include <cmath>
#include "2DVec.h"
#include "commons.h"

class Entity
{
private:
	float mass;
	vec pos;
	vec vel;
	float density;
	color4f color;
public:
	Entity(float mass, vec pos, vec vel, float density, color4f color);
	virtual float getMass() const;
	virtual void setMass(float value);
	virtual void gainMass(float value);
	virtual vec getPos() const;
	virtual void setPos(vec pos);
	virtual vec getVel() const;
	virtual void setVel(vec vel);
	virtual float getDensity() const;
	virtual void setDensity(float value);
	virtual float getRadius() const;
	virtual color4f getColor() const;
	virtual void setColor(color4f color);
	virtual int getSign();
	virtual void move(vec force, float time);
	virtual vec getAccelerationAt(vec pos) const;
	virtual vec getForceAt(Entity * e) const;
	static bool areColliding(Entity * e1, Entity * e2);
	static void elasticCollision(Entity * e1, Entity * e2);
	static void inelasticCollision(Entity * e1, Entity * e2);
	~Entity();
};