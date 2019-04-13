#pragma once
#include "Entity.h"

Entity::Entity(float mass, vec pos, vec vel, float density, color4f color)
{
	this->mass = mass;
	this->pos = pos;
	this->vel = vel;
	this->density = density;
	this->color = color;
}

float Entity::getMass() const
{
	return this->mass;
}

void Entity::setMass(float value) 
{
	this->setVel(vecmul(this->getVel(), this->getMass() / value));
	this->mass = value;
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

float Entity::getDensity() const
{
	return this->density;
}

void Entity::setDensity(float value)
{
	this->density = value;
}

float Entity::getRadius() const
{
	return abs(this->getMass()) / this->getDensity();
}

color4f Entity::getColor() const
{
	return this->color;
}

void Entity::setColor(color4f color)
{
	this->color = color;
}

void Entity::move(vec force, float time)
{
	vec acc = force;
	acc.x /= abs(this->getMass());
	acc.y /= abs(this->getMass());
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
	if (dist < density)
		return acc;
	acc.x = GRAV_CONSTANT * this->getMass() * (this->getPos().x - pos.x) / pow(dist, 3);
	acc.y = GRAV_CONSTANT * this->getMass() * (this->getPos().y - pos.y) / pow(dist, 3);
	return acc;
}

vec Entity::getForceAt(Entity * e) const
{
	vec force = this->getAccelerationAt(e->getPos());
	if (e->getMass() <= 0.01 && e->getMass() >= -0.01)
	{
		force.x = 0;
		force.y = 0;
	} 
	else
	{
		force.x *= e->getMass();
		force.y *= e->getMass();
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
	
	vec v1 = e1->getVel();
	vec v2 = e2->getVel();
	vec p1 = e1->getPos();
	vec p2 = e2->getPos();
	float m1 = abs(e1->getMass());
	float m2 = abs(e2->getMass());
	float r1 = e1->getRadius();
	float r2 = e2->getRadius();

	vec newV1, newV2, newP1, newP2;

	newV1 = vecdiff(v1, vecmul(vecdiff(p1, p2), 2 * m2 / (m1 + m2) * scalprod(vecdiff(v1, v2), vecdiff(p1, p2)) / scalprod(vecdiff(p1, p2), vecdiff(p1, p2))));
	newV2 = vecdiff(v2, vecmul(vecdiff(p2, p1), 2 * m1 / (m1 + m2) * scalprod(vecdiff(v2, v1), vecdiff(p2, p1)) / scalprod(vecdiff(p2, p1), vecdiff(p2, p1))));
	e1->setVel(newV1);
	e2->setVel(newV2);

	vec d = vecmul(vecdiff(p2, p1), 1 / norm(vecdiff(p2, p1)));

	while (Entity::areColliding(e1, e2))
	{
		newP1 = vecsum(p1, vecmul(d, -(r1 + r2 - norm(vecdiff(p2, p1))) / 2.0f));
		newP2 = vecsum(p2, vecmul(d, +(r1 + r2 - norm(vecdiff(p1, p2))) / 2.0f));
		e1->setPos(newP1);
		e2->setPos(newP2);
		d = vecmul(d, 1.01f);
	}
}

Entity::~Entity()
{
}