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

float Entity::getRadius() const
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

	if (this->getPos().x > 400)
	{
		this->setPos(vec{ 400.0f, this->getPos().y });
		this->setVel(vec{ -this->getVel().x, this->getVel().y });
	}
	if (this->getPos().x < -400)
	{
		this->setPos(vec{ -400.0f, this->getPos().y });
		this->setVel(vec{ -this->getVel().x, this->getVel().y });
	}
	if (this->getPos().y > 300)
	{
		this->setPos(vec{ this->getPos().x, 300.0f });
		this->setVel(vec{ this->getVel().x, -this->getVel().y });
	}
	if (this->getPos().y < -300)
	{
		this->setPos(vec{ this->getPos().x, -300.0f });
		this->setVel(vec{ this->getVel().x, -this->getVel().y });
	}

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

bool Entity::areColliding(Entity * e1, Entity * e2) 
{
	float dist = sqrt(pow(e1->getPos().x - e2->getPos().x, 2) + pow(e1->getPos().y - e2->getPos().y, 2));
	return dist < (e1->getRadius() + e2->getRadius());
}

void Entity::handleCollision(Entity * e1, Entity * e2)
{
	if (!Entity::areColliding(e1, e2))
		return;
	vec v1{ 0.0f, 0.0f };
	vec v2{ 0.0f, 0.0f };
	//v1.x = (e1->getMass() - e1->getMass()) / (e1->getMass() + e2->getMass())*e1->getVel().x +
	//	(e2->getMass() * 2) / (e1->getMass() + e2->getMass())*e2->getVel().x;
	//v1.y = (e1->getMass() - e1->getMass()) / (e1->getMass() + e2->getMass())*e1->getVel().y +
	//	(e2->getMass() * 2) / (e1->getMass() + e2->getMass())*e2->getVel().y;
	//v2.x = (e1->getMass() * 2) / (e1->getMass() + e2->getMass())*e1->getVel().x +
	//	(e2->getMass() - e1->getMass()) / (e1->getMass() + e2->getMass())*e2->getVel().x;
	//v2.y = (e1->getMass() * 2) / (e1->getMass() + e2->getMass())*e1->getVel().y +
	//	(e2->getMass() - e1->getMass()) / (e1->getMass() + e2->getMass())*e2->getVel().y;
	v1 = vecdiff(e1->getVel(), vecmul(vecdiff(e1->getPos(), e2->getPos()), 2 * e2->getMass() / (e1->getMass() + e2->getMass()) * scalprod(vecdiff(e1->getVel(), e2->getVel()), vecdiff(e1->getPos(), e2->getPos())) / scalprod(vecdiff(e1->getPos(), e2->getPos()), vecdiff(e1->getPos(), e2->getPos()))));
	v2 = vecdiff(e2->getVel(), vecmul(vecdiff(e2->getPos(), e1->getPos()), 2 * e1->getMass() / (e1->getMass() + e2->getMass()) * scalprod(vecdiff(e2->getVel(), e1->getVel()), vecdiff(e2->getPos(), e1->getPos())) / scalprod(vecdiff(e2->getPos(), e1->getPos()), vecdiff(e2->getPos(), e1->getPos()))));
	e1->setVel(v1);
	e2->setVel(v2);
}

Entity::~Entity()
{
}