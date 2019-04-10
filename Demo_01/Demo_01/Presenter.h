#pragma once
#include <vector>
#include <chrono>
#include "View.h"
#include "Entity.h"
#include "CommandListener.h"
#include "Player.h"

#define THRUST_FORCE 100.0f

class Presenter :
	public CommandListener
{
private: 
	std::vector<Entity*> * entities;
	bool keys[COMMANDS];
	Player * player;
	View * view;
	std::chrono::high_resolution_clock::time_point lastFrame;

	virtual void presentEntity(Entity * entity);
	virtual void moveEntities(float time);
	virtual void movePlayer(float time);
	virtual void handleCollisions();
	virtual float getFrameTime();
	virtual color4f randomEntityColor();
public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

