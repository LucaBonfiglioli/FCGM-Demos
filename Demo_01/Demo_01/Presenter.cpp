#pragma once
#include "Presenter.h"
#include "OpenGLView.h"
#include <iostream>

Presenter::Presenter()
{
	this->entities = new std::vector<Entity*>();
	this->view = new OpenGLView();
	this->player = new Entity(1.0f, 500.0f, vec{ 200.0f, 200.0f }, vec{ 0.0f, 0.0f }, 10.0f);
	
	for (int i = 0; i < COMMANDS; i++)
		this->keys[i] = false;

	entities->push_back(new Entity(50.0f, 1000.0f, vec{ -50.0f, 0.0f }, vec{ 0.0f, 8.0f }, 20.0f));
	entities->push_back(new Entity(50.0f, 1000.0f, vec{ +50.0f, 0.0f }, vec{ 0.0f, -8.0f }, 20.0f));
	entities->push_back(new Entity(50.0f, 1000.0f, vec{ 0.0f, 50.0f }, vec{ 5.0f, -3.0f }, 20.0f));

	this->lastFrame = std::chrono::high_resolution_clock::now();
}

void Presenter::receive(Command cmd)
{
	this->keys[cmd] = !this->keys[cmd];
}

void Presenter::startGameLoop()
{
	this->view->startGameLoop(this);
}

float Presenter::getFrameTime()
{
	std::chrono::high_resolution_clock::time_point curtime = std::chrono::high_resolution_clock::now();
	long long frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(curtime - this->lastFrame).count();
	this->lastFrame = curtime;
	float frameTimeMillis = (float)frameTime / 1000000000;
	return frameTimeMillis;
}

void Presenter::moveEntities(float time)
{
	for (int i = 0; i < this->entities->size(); i++)
	{
		vec totalForce{ 0.0f, 0.0f };
		for (int j = 0; j < this->entities->size(); j++)
		{
			if (i == j)
				continue;
			vec force = this->entities->at(j)->getForceAt(this->entities->at(i));
			totalForce.x += force.x;
			totalForce.y += force.y;
		}

		this->entities->at(i)->move(totalForce, time);
	}
}

void Presenter::movePlayer(float time)
{
	vec playerForce{ 0.0f, 0.0f };
	for (int j = 0; j < this->entities->size(); j++)
	{
		vec force = this->entities->at(j)->getForceAt(this->player);
		playerForce.x += force.x;
		playerForce.y += force.y;
	}
	if (this->keys[FORWARD])
		playerForce.y += THRUST_FORCE;
	if (this->keys[BACK])
		playerForce.y -= THRUST_FORCE;
	if (this->keys[LEFT])
		playerForce.x -= THRUST_FORCE;
	if (this->keys[RIGHT])
		playerForce.x += THRUST_FORCE;
	this->player->move(playerForce, time);
}

void Presenter::handleCollisions()
{
	for (int i = 0; i < this->entities->size(); i++)
		for (int j = i+1; j < this->entities->size(); j++)
		{
			if (i == j) continue;
			Entity::handleCollision(this->entities->at(i), this->entities->at(j));
		}

	for (int i = 0; i < this->entities->size(); i++)
		Entity::handleCollision(this->player, this->entities->at(i));
}

void Presenter::gameLoop()
{
	float frameTimeMillis = this->getFrameTime();

	this->handleCollisions();

	this->moveEntities(frameTimeMillis);
	this->movePlayer(frameTimeMillis);

	for (int i = 0; i < this->entities->size(); i++)
		this->presentEntity(this->entities->at(i));
	this->presentEntity(this->player);

	view->drawScene();
}

void Presenter::presentEntity(Entity * entity)
{
	view->drawCircle(entity->getPos().x, entity->getPos().y, entity->getRadius());
}

Presenter::~Presenter()
{
}
