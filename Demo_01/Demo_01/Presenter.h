#pragma once
#include <vector>
#include <chrono>
#include "View.h"
#include "Entity.h"
#include "CommandListener.h"

#define THRUST_FORCE 100.0f

class Presenter :
	public CommandListener
{
private: 
	std::vector<Entity*> * entities;
	bool keys[COMMANDS];
	Entity * player;
	View * view;
	std::chrono::high_resolution_clock::time_point lastFrame;
	virtual void presentEntity(Entity * entity);
public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

