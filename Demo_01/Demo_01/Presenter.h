#pragma once
#include <vector>
#include <chrono>
#include "View.h"
#include "Entity.h"
#include "CommandListener.h"
#include "Player.h"

class Presenter :
	public CommandListener
{
private: 
	std::vector<Entity*> * entities;
	Player * player;
	View * view;
	std::chrono::high_resolution_clock::time_point lastFrame;
	bool keys[COMMANDS];
	bool playerDampeners;
	float initialEnergy;

	virtual void newGame();
	virtual void presentEntities();
	virtual void moveEntities(float time);
	virtual void movePlayer(float time);
	virtual void handleCollisions();
	virtual float getFrameTime();
	virtual void addEntity();
	virtual void removeEntity(int index);
	virtual void cleanSingleHitInputs();
	virtual float calculateEnergy();
public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

