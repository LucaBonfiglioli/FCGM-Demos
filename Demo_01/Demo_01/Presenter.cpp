#pragma once
#include "Presenter.h"
#include "OpenGLView.h"
#include <iostream>

Presenter::Presenter()
{
	this->entities = new std::vector<Entity*>();
	this->view = new OpenGLView();
	this->player = new Entity(50.0f, 500.0f, vec{ 0.0f, 0.0f }, vec{ 0.0f, 0.0f });
	
	for (int i = 0; i < COMMANDS; i++)
		this->keys[i] = false;

	entities->push_back(new Entity(50.0f, 50.0f, vec{ -50.0f, 0.0f }, vec{ 0.0f, 0.6f }));
	entities->push_back(new Entity(50.0f, 50.0f, vec{ +50.0f, 0.0f }, vec{ 0.0f, -0.6f }));
}

void Presenter::receive(Command cmd)
{
	this->keys[cmd] = !this->keys[cmd];
}

void Presenter::startGameLoop()
{
	this->view->startGameLoop(this);
}

void Presenter::gameLoop()
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
		this->entities->at(i)->move(totalForce, 1.0f);
		this->presentEntity(this->entities->at(i));
	}

	vec playerForce{ 0.0f, 0.0f };
	for (int j = 0; j < this->entities->size(); j++)
	{
		vec force = this->entities->at(j)->getForceAt(this->player);
		playerForce.x += force.x;
		playerForce.y += force.y;
	}
	if (this->keys[FORWARD])
		playerForce.y += 5.f;
	if (this->keys[BACK])
		playerForce.y -= 5.f;
	if (this->keys[LEFT])
		playerForce.x -= 5.f;
	if (this->keys[RIGHT])
		playerForce.x += 5.f;
	this->player->move(playerForce, 1.0f);

	if (player->getPos().x > 400)
	{
		player->setPos(vec{ 400.0f, player->getPos().y });
		player->setVel(vec{ -player->getVel().x, player->getVel().y });
	}
	if (player->getPos().x < -400)
	{
		player->setPos(vec{ -400.0f, player->getPos().y });
		player->setVel(vec{ -player->getVel().x, player->getVel().y });
	}
	if (player->getPos().y > 300)
	{
		player->setPos(vec{ player->getPos().x, 300.0f });
		player->setVel(vec{ player->getVel().x, -player->getVel().y });
	}
	if (player->getPos().y < -300)
	{
		player->setPos(vec{ player->getPos().x, -300.0f });
		player->setVel(vec{ player->getVel().x, -player->getVel().y });
	}

	this->presentEntity(this->player);

	view->drawScene();
}

void Presenter::presentEntity(Entity * entity)
{
	view->drawTriangle(entity->getPos().x, entity->getPos().y);
}

Presenter::~Presenter()
{
}
