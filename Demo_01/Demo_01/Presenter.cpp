#pragma once
#include "Presenter.h"
#include "OpenGLView.h"

Presenter::Presenter()
{
	this->entities = new std::vector<Entity*>();
	this->particles = new std::vector<Entity*>();
	this->view = new OpenGLView();
	this->player = NULL;
	this->newGame();

	this->playerDampeners = false;

	for (int i = 0; i < COMMANDS; i++)
		this->keys[i] = false;

	this->lastFrame = std::chrono::high_resolution_clock::now();
	this->updateFrameTime();
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

void Presenter::updateFrameTime()
{
	std::chrono::high_resolution_clock::time_point curtime = std::chrono::high_resolution_clock::now();
	long long frameTimeNanos = std::chrono::duration_cast<std::chrono::nanoseconds>(curtime - this->lastFrame).count();
	this->lastFrame = curtime;
	float frameTime = (float)frameTimeNanos / GAME_SPEED;
	this->frameTime = frameTime;
}

Entity * Presenter::randomEntity()
{
	float mass = rand_u(ENTITY_MASS_MIN, ENTITY_MASS_MAX);
	vec pos
	{ 
		rand_u(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2),
		rand_u(-SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2)
	};
	vec vel{ 0.0f, 0.0f };
	float density = rand_u(ENTITY_DENSITY_MIN, ENTITY_DENSITY_MAX);
	
	int sign = rand_b() * 2 - 1;

	color4f c = this->getEntityColor(sign, density);
	
	Entity * e = new Entity(sign*mass, pos, vel, density, c);
	return e;
}

void Presenter::addEntity(Entity * e)
{
	this->entities->push_back(e);
}

void Presenter::removeEntity(int index)
{
	this->entities->erase(this->entities->begin() + index);
}

color4f Presenter::getEntityColor(int sign, float density)
{
	color4f c;
	if (sign > 0)
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
	return c;
}

void Presenter::addParticle(Entity * e)
{
	this->particles->push_back(e);
}

void Presenter::removeParticle(int index)
{
	delete this->particles->at(index);
	this->particles->erase(this->particles->begin() + index);
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

void Presenter::moveEntities()
{
	float time = this->frameTime;

	float r = rand_u(0.0f, 1.0f);
	if (r < time * ENTITY_SPAWN_CHANCE)
	{
		this->addEntity(this->randomEntity());
	}

	for (int i = 0; i < this->entities->size(); i++)
	{
		Entity * e = this->entities->at(i);
		vec totalForce{ 0.0f, 0.0f };
		vec force{ 0.0f, 0.0f };
		for (int j = 0; j < this->entities->size(); j++)
		{
			if (i == j)
				continue;
			force = this->entities->at(j)->getForceAt(e);
			totalForce.x += force.x;
			totalForce.y += force.y;
		}

		force = this->player->getForceAt(e);
		totalForce.x += force.x;
		totalForce.y += force.y;

		e->move(totalForce, time);

		this->bounceOnBorders(e);
	}
}

void Presenter::bounceOnBorders(Entity * e)
{
	if (e->getPos().x > (float)SCREEN_WIDTH / 2.0f)
	{
		e->setPos(vec{ (float)SCREEN_WIDTH / 2.0f, e->getPos().y });
		e->setVel(vec{ -e->getVel().x, e->getVel().y });
	}
	if (e->getPos().x < -(float)SCREEN_WIDTH / 2.0f)
	{
		e->setPos(vec{ -(float)SCREEN_WIDTH / 2.0f, e->getPos().y });
		e->setVel(vec{ -e->getVel().x, e->getVel().y });
	}
	if (e->getPos().y > (float)SCREEN_HEIGHT / 2.0f)
	{
		e->setPos(vec{ e->getPos().x, (float)SCREEN_HEIGHT / 2.0f });
		e->setVel(vec{ e->getVel().x, -e->getVel().y });
	}
	if (e->getPos().y < -(float)SCREEN_HEIGHT / 2.0f)
	{
		e->setPos(vec{ e->getPos().x, -(float)SCREEN_HEIGHT / 2.0f });
		e->setVel(vec{ e->getVel().x, -e->getVel().y });
	}
}

void Presenter::movePlayer()
{
	float time = this->frameTime;
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
	this->bounceOnBorders(player);
}

void Presenter::moveParticles()
{
	float time = this->frameTime;

	for (int i = 0; i < this->entities->size(); i++)
	{
		Entity * e = this->entities->at(i);
		float r = rand_u(0.0f, 1.0f);
		if (r < time * PARTICLE_SPAWN_CHANCE)
		{
			float mass = ENTITY_MASS_MAX / 6;
			vec vel = vecmul({1.0f, 0.0f}, - sqrt(norm(e->getVel()) * e->getRadius()) * rand_u(1.0f, PARTICLE_SPEED_RANGE + 1.0f));
			float angle = rand_u(0.0f, 2*PI);
			vec rvel = { vel.x * cos(angle) - vel.y * sin(angle), vel.x * sin(angle) + vel.y * cos(angle) };
			vec pos = vecsum(e->getPos(), vecmul(rvel, e->getRadius() / norm(rvel)));
			float density = ENTITY_DENSITY_MAX;
			color4f color = e->getColor();
			color.b /= PARTICLE_COLOR_COEFF, color.g /= PARTICLE_COLOR_COEFF, color.r /= PARTICLE_COLOR_COEFF;
			this->addParticle(new Entity(mass, pos, rvel, density, color));
		}
	}

	for (int i = 0; i < this->particles->size(); i++)
	{
		Entity * p = this->particles->at(i);
		if (p->getColor().a <= 0.0f)
		{
			this->removeParticle(i);
			i--;
			continue;
		}
		p->move(vec{ 0.0f, 0.0f }, time);

		color4f color = p->getColor();
		float fading = 1.0f - color.a;
		float dFading = time * PARTICLE_FADING_SPEEED;
		color.a -= dFading;
		p->setMass(p->getMass()*(PARTICLE_SCALING - fading + 1.0f)/(PARTICLE_SCALING - fading - dFading + 1.0f));
		p->setColor(color);
	}
}

void Presenter::handleCollisions()
{
	for (int i = 0; i < this->entities->size(); i++)
		for (int j = i+1; j < this->entities->size(); j++)
		{
			if (i == j) continue;
			Entity::inelasticCollision(this->entities->at(i), this->entities->at(j));
		}

	for (int i = 0; i < this->entities->size(); i++)
		Entity::inelasticCollision(this->player, this->entities->at(i));

	for (int i = 0; i < this->entities->size(); i++)
	{
		if (this->entities->at(i)->getMass() < 0.01 && this->entities->at(i)->getMass() > -0.01)
		{
			this->removeEntity(i);
			i--;
			continue;
		}
		this->entities->at(i)->setColor(this->getEntityColor(this->entities->at(i)->getSign(), this->entities->at(i)->getDensity()));
	}

	if (this->player->getMass() < 0.01 && this->player->getMass() > -0.01)
		this->newGame();
}

void Presenter::gameLoop()
{
	this->updateModel();
	this->presentScene();
	this->cleanSingleHitInputs();
	view->drawScene();
}

void Presenter::updateModel()
{
	this->updateFrameTime();
	if (this->keys[RESET])
		this->newGame();
	this->handleCollisions();
	this->moveEntities();
	this->movePlayer();
	this->moveParticles();
}

void Presenter::newGame()
{
	int entities = this->entities->size();
	for (int i = 0; i < entities; i++)
		this->removeEntity(0);

	int particles = this->particles->size();
	for (int i = 0; i < particles; i++)
		this->removeParticle(0);

	if (this->player != NULL)
		delete this->player;

	this->player = new Player(PLAYER_MASS, PLAYER_POS, PLAYER_VEL, PLAYER_DENSITY, PLAYER_COLOR);

	for (int i = 0; i < ENTITIES; i++)
		this->addEntity(this->randomEntity());

	this->initialEnergy = this->calculateEnergy();
}

void Presenter::presentScene()
{
	Entity * entity;

	// Particles
	for (int i = 0; i < this->particles->size(); i++)
	{
		entity = this->particles->at(i);
		view->drawCircle(entity->getPos().x, entity->getPos().y, entity->getRadius(), entity->getColor());
	}

	// Entities annulus
	for (int i = 0; i < this->entities->size(); i++)
	{
		entity = this->entities->at(i);
		float innerRad = entity->getRadius() + ANNULUS_INRAD_SCALING * (abs(entity->getMass())) / ENTITY_MASS_MAX;
		float outerRad = innerRad + ANNULUS_THICKNESS;
		view->drawAnnulus(entity->getPos().x, entity->getPos().y, innerRad, outerRad, ANNULUS_COLOR);
	}
	
	// Player annuli
	view->drawAnnulus(player->getPos().x, player->getPos().y, player->getRadius() * 2, player->getRadius() * 2 + 5.0f, PLAYER_COLOR);
	view->drawAnnulus(player->getPos().x, player->getPos().y, player->getRadius() * 3, player->getRadius() * 3 + 5.0f, PLAYER_COLOR);
	
	// Entities body
	for (int i = 0; i < this->entities->size(); i++)
	{
		entity = this->entities->at(i);
		view->drawCircle(entity->getPos().x, entity->getPos().y, entity->getRadius(), entity->getColor());
		float innerRad = entity->getRadius() * ENTITY_BORDER_SCALING;
		float outerRad = entity->getRadius() + 1.0f;
		color4f color = entity->getColor();
		color.r /= ENTITY_BORDER_COLOR_COEFF; 
		color.g /= ENTITY_BORDER_COLOR_COEFF;
		color.b /= ENTITY_BORDER_COLOR_COEFF;
		view->drawAnnulus(entity->getPos().x, entity->getPos().y, innerRad, outerRad, color);
	}
	
	// player body
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
