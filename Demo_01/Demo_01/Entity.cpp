#pragma once
#include "Entity.h"

Entity::Entity(float mass, float gmass, vec pos, vec vel, float radius)
{
	this->mass = mass;
	this->gmass = gmass;
	this->pos = pos;
	this->vel = vel;
	this->radius = radius;
}


float Entity::getMass() const
{
	return this->mass;
}

void Entity::setMass(float value) 
{
	this->mass = value;
}

float Entity::getGmass() const
{
	return this->gmass;
}

void Entity::setGmass(float value)
{
	this->gmass = value;
}

vec Entity::getPos() const
{
	return this->pos;
}

void Entity::setPos(vec pos)
{
	this->pos = pos;
}

vec Entity::getVel() const
{
	return this->vel;
}

void Entity::setVel(vec vel)
{
	this->vel = vel;
}

float Entity::getRadius()
{
	return this->radius;
}

void Entity::setRadius(float value)
{
	this->radius = value;
}

void Entity::move(vec force, float time)
{
	if (this->getMass() <= 0)
		return;
	vec acc = force;
	acc.x /= this->getMass();
	acc.y /= this->getMass();
	vec pos = this->getPos();
	pos.x += 1 / 2 * acc.x * pow(time, 2) + this->getVel().x * time;
	pos.y += 1 / 2 * acc.y * pow(time, 2) + this->getVel().y * time;
	this->setPos(pos);
	vec vel = this->getVel();
	vel.x += acc.x * time;
	vel.y += acc.y * time;
	this->setVel(vel);
}

vec Entity::getAccelerationAt(vec pos) const
{
	vec acc{ 0.0f, 0.0f };
	float dist = sqrt(pow(pos.x - this->getPos().x, 2) + pow(pos.y - this->getPos().y, 2));
	if (dist < radius)
		return acc;
	acc.x = this->getGmass() * (this->getPos().x - pos.x) / pow(dist, 3);
	acc.y = this->getGmass() * (this->getPos().y - pos.y) / pow(dist, 3);
	return acc;
}

vec Entity::getForceAt(Entity * e) const
{
	vec force = this->getAccelerationAt(e->getPos());
	if (e->getMass() <= 0)
	{
		force.x = 0;
		force.y = 0;
	} 
	else
	{
		force.x *= e->getGmass();
		force.y *= e->getGmass();
	}
	return force;
}

Entity::~Entity()
{
}