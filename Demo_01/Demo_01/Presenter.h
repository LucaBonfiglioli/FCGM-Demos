#pragma once
#include <vector>
#include <chrono>
#include "View.h"
#include "Entity.h"
#include "CommandListener.h"
#include "Player.h"
#include "rand_util.h"

class Presenter :
	public CommandListener
{
private: 
	std::vector<Entity*> * entities;
	std::vector<Entity*> * particles;
	std::vector<Entity*> * entitiesToSpawn;
	std::vector<float> * entitiesToSpawnTimers;
	Player * player;
	View * view;
	std::chrono::high_resolution_clock::time_point lastFrame;
	float frameTime;
	bool keys[COMMANDS];
	bool playerDampeners;
	float initialEnergy;

	virtual void newGame();
	virtual void presentScene();
	virtual void updateModel();
	virtual void moveEntities();
	virtual void movePlayer();
	virtual void moveParticles();
	virtual void handleCollisions();
	virtual void bounceOnBorders(Entity * e);
	virtual void updateFrameTime();
	virtual color4f getEntityColor(int sign, float density);
	virtual Entity * randomEntity(float sign_prob);
	virtual void addEntity(Entity * e);
	virtual void removeEntity(int index);
	virtual void addEntityToSpawn(Entity * e);
	virtual void removeEntityToSpawn(int index, bool del);
	virtual void addParticle(Entity * e);
	virtual void removeParticle(int index);
	virtual void cleanSingleHitInputs();
	virtual float calculateEnergy();
	virtual int entitiesCount(int sign);
	virtual float entitySpawnChance();
	virtual void victory();
	virtual void defeat();

public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

