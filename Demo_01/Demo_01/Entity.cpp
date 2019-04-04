#include "Entity.h"



Entity::Entity(float mass, float gmass, vec pos, vec vel)
{
	this->mass = mass;
	this->gmass = gmass;
	this->pos = pos;
	this->vel = vel;
}


float Entity::getMass() 
{
	return this->mass;
}

void Entity::setMass(float value) 
{
	this->mass = value;
}

float Entity::getGmass()
{
	return this->gmass;
}

void Entity::setGmass(float value)
{
	this->gmass = value;
}

vec Entity::getPos()
{
	return this->pos;
}

void Entity::setPos(vec pos)
{
	this->pos = pos;
}

vec Entity::getVel()
{
	return this->vel;
}

void Entity::setVel(vec vel)
{
	this->vel = vel;
}

void Entity::move(vec force, float time)
{

}

vec Entity::getAccelerationAt(vec pos)
{
	vec acc;
	float dist = sqrt(pow(pos.x - this->getPos().x, 2) + pow(pos.y - this->getPos().y, 2));
	acc.x = this->getGmass() * (this->getPos().x - pos.x) / pow(dist, 3);
	acc.y = this->getGmass() * (this->getPos().y - pos.y) / pow(dist, 3);
	return acc;
}

Entity::~Entity()
{
}
