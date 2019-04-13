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
	virtual void updateFrameTime();
	virtual Entity * randomEntity();
	virtual void addEntity(Entity * e);
	virtual void removeEntity(int index);
	virtual void addParticle(Entity * e);
	virtual void removeParticle(int index);
	virtual void cleanSingleHitInputs();
	virtual float calculateEnergy();
public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

