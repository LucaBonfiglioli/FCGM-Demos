#pragma once
#include <vector>
#include "View.h"
#include "Entity.h"
#include "CommandListener.h"

class Presenter :
	public CommandListener
{
private: 
	std::vector<Entity*> * entities;
	bool keys[COMMANDS];
	Entity * player;
	View * view;
	virtual void presentEntity(Entity * entity);
public:
	Presenter();
	virtual void receive(Command cmd);
	virtual void startGameLoop();
	virtual void gameLoop();
	~Presenter();
};

