#pragma once
#include "Presenter.h"
#include "OpenGLView.h"
#include <iostream>
#include <ctime>
#include <random>

Presenter::Presenter()
{
	this->entities = new std::vector<Entity*>();
	this->view = new OpenGLView();
	this->player = NULL;
	this->newGame();

	this->playerDampeners = false;

	for (int i = 0; i < COMMANDS; i++)
		this->keys[i] = false;

	this->lastFrame = std::chrono::high_resolution_clock::now();
}

void Presenter::receive(Command cmd)
{
	static bool keyUp[COMMANDS] = { false };

	if (!singleHit[cmd])
		this->keys[cmd] = !this->keys[cmd];
	else if (!keyUp[cmd])
	{
		this->keys[cmd] = true;
		keyUp[cmd] = true;
	}
	else
		keyUp[cmd] = false;
}

void Presenter::startGameLoop()
{
	this->view->startGameLoop(this);
}

float Presenter::getFrameTime()
{
	std::chrono::high_resolution_clock::time_point curtime = std::chrono::high_resolution_clock::now();
	long long frameTimeNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(curtime - this->lastFrame).count();
	this->lastFrame = curtime;
	float frameTime = (float)frameTimeNanos / GAME_SPEED;
	return frameTime;
}

void Presenter::addEntity()
{
	float mass = ((float)rand() / (float)RAND_MAX) * (ENTITY_MASS_MAX - ENTITY_MASS_MIN) + ENTITY_MASS_MIN;
	vec pos
	{ 
		((float)rand() / (float)RAND_MAX) * SCREEN_WIDTH - SCREEN_WIDTH / 2,
		((float)rand() / (float)RAND_MAX) * SCREEN_HEIGHT - SCREEN_HEIGHT / 2
	};
	vec vel{ 0.0f, 0.0f };
	float density = ((float)rand() / (float)RAND_MAX) * (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN) + ENTITY_DENSITY_MIN;
	
	int neg = (rand() % 2) * 2 - 1;
	//neg = abs(neg);

	color4f c = ENTITY_BASE_COLOR;

	if (neg > 0)
	{
		c = ENTITY_BASE_COLOR;
		c.r += ENTITY_COLOR_RANGE.r * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
		c.g += ENTITY_COLOR_RANGE.g * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
		c.b += ENTITY_COLOR_RANGE.b * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
	}
	else
	{
		c = ENTITY_BASE_COLOR_NEG;
		c.r += ENTITY_COLOR_RANGE_NEG.r * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
		c.g += ENTITY_COLOR_RANGE_NEG.g * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
		c.b += ENTITY_COLOR_RANGE_NEG.b * (density - ENTITY_DENSITY_MIN) / (ENTITY_DENSITY_MAX - ENTITY_DENSITY_MIN);
	}
	Entity * e = new Entity(neg*mass, pos, vel, density, c);
	this->entities->push_back(e);
}

void Presenter::removeEntity(int index)
{
	Entity * e = this->entities->at(index);
	this->entities->erase(this->entities->begin() + index);
	delete e;
}

void Presenter::cleanSingleHitInputs()
{
	for (int i = 0; i < COMMANDS; i++)
		if (singleHit[i])
			this->keys[i] = false;
}

float Presenter::calculateEnergy()
{
	float result = 0.0f;
	for (int i = 0; i < this->entities->size(); i++)
	{
		result += 0.5f * this->entities->at(i)->getMass() *
			pow(norm(this->entities->at(i)->getVel()), 2);
		for (int j = i + 1; j < this->entities->size(); j++)
		{
			result -= GRAV_CONSTANT * this->entities->at(i)->getMass() * this->entities->at(j)->getMass()
				/ norm(vecdiff(this->entities->at(i)->getPos(), this->entities->at(j)->getPos()));
		}
		result -= GRAV_CONSTANT * this->entities->at(i)->getMass() * this->player->getMass() 
			/ norm(vecdiff(this->entities->at(i)->getPos(), this->player->getPos()));
	}
	result += 0.5f * this->player->getMass() * pow(norm(this->player->getVel()), 2);
	return result;
}

void Presenter::moveEntities(float time)
{
	for (int i = 0; i < this->entities->size(); i++)
	{
		vec totalForce{ 0.0f, 0.0f };
		vec force{ 0.0f, 0.0f };
		for (int j = 0; j < this->entities->size(); j++)
		{
			if (i == j)
				continue;
			force = this->entities->at(j)->getForceAt(this->entities->at(i));
			totalForce.x += force.x;
			totalForce.y += force.y;
		}

		force = this->player->getForceAt(this->entities->at(i));
		totalForce.x += force.x;
		totalForce.y += force.y;

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
	vec thrust{ 0.0f, 0.0f };
	if (this->keys[TOGGLE_DAMPENERS])
		this->playerDampeners = !this->playerDampeners;
	if (!this->playerDampeners)
	{
		if (this->keys[FORWARD])
			thrust.y += 1.0f;
		if (this->keys[BACK])
			thrust.y -= 1.0f;
		if (this->keys[LEFT])
			thrust.x -= 1.0f;
		if (this->keys[RIGHT])
			thrust.x += 1.0f;
		if (norm(thrust) > 0.01f)
			thrust = vecmul(thrust, THRUST_FORCE / norm(thrust));
	}
	else
	{
		if (norm(player->getVel()) > 0.01f)
			thrust = vecmul(player->getVel(), - THRUST_FORCE / norm(player->getVel()));
	}
	if (norm(thrust) > 0 && this->player->getFuel() > 0)
	{
		playerForce = vecsum(playerForce, thrust);
		this->player->consumeFuel(time);
	}
	if (norm(thrust) <= 0.01f)
	{
		this->player->refillFuel(time);
	}
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

	static bool reset = false;

	if (this->keys[RESET])
		this->newGame();

	this->handleCollisions();

	this->moveEntities(frameTimeMillis);
	this->movePlayer(frameTimeMillis);

	this->presentEntities();
	//std::cout << this->calculateEnergy() / this->initialEnergy << "\n";

	this->cleanSingleHitInputs();

	view->drawScene();
}

void Presenter::newGame()
{
	for (int i = 0; i < this->entities->size(); i++)
		this->removeEntity(i);

	if (this->player != NULL)
		delete this->player;

	this->player = new Player(PLAYER_MASS, PLAYER_POS, PLAYER_VEL, PLAYER_DENSITY, PLAYER_COLOR);

	for (int i = 0; i < ENTITIES; i++)
		this->addEntity();

	this->initialEnergy = this->calculateEnergy();
}

void Presenter::presentEntities()
{
	Entity * entity;

	view->drawAnnulus(player->getPos().x, player->getPos().y, player->getRadius() * 2, player->getRadius() * 2 + 5.0f, PLAYER_COLOR);
	view->drawAnnulus(player->getPos().x, player->getPos().y, player->getRadius() * 3, player->getRadius() * 3 + 5.0f, PLAYER_COLOR);

	for (int i = 0; i < this->entities->size(); i++)
	{
		entity = this->entities->at(i);
		float innerRad = entity->getRadius() + ANNULUS_INRAD_SCALING * (abs(entity->getMass()) - ENTITY_MASS_MIN) / (ENTITY_MASS_MAX - ENTITY_MASS_MIN);
		float outerRad = innerRad + ANNULUS_THICKNESS;
		view->drawAnnulus(entity->getPos().x, entity->getPos().y, innerRad, outerRad, ANNULUS_COLOR);
	}
	for (int i = 0; i < this->entities->size(); i++)
	{
		entity = this->entities->at(i);
		view->drawCircle(entity->getPos().x, entity->getPos().y, entity->getRadius(), entity->getColor());
		float innerRad = entity->getRadius() * 9/10;
		float outerRad = entity->getRadius() + 1.0f;
		color4f color = entity->getColor();
		color.r /= 2.0; 
		color.g /= 2.0; 
		color.b /= 2.0;
		view->drawAnnulus(entity->getPos().x, entity->getPos().y, innerRad, outerRad, color);
	}
	
	view->drawCircle(player->getPos().x, player->getPos().y, player->getRadius(), player->getColor());

}

Presenter::~Presenter()
{
	for (int i = 0; i < this->entities->size(); i++)
		this->removeEntity(i);
	delete this->entities;
	delete this->player;
	delete this->view;
}
