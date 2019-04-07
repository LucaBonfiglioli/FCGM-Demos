#include "OpenGLCommandEmitter.h"

OpenGLCommandEmitter::OpenGLCommandEmitter()
{
	this->listeners = new std::vector<CommandListener*>();
}

void OpenGLCommandEmitter::sub(CommandListener * listener)
{
	this->listeners->push_back(listener);
}

void OpenGLCommandEmitter::unsub(CommandListener * listener)
{
	int i = 0;
	bool found = false;
	for (; i < this->listeners->size(); i++)
		if (this->listeners->at(i) == listener) {
			found = true;
			break;
		}
	if (found)
		this->listeners->erase(this->listeners->begin()+i);
}

void OpenGLCommandEmitter::emit(Command cmd)
{
	for (int i = 0; i < this->listeners->size(); i++)
		this->listeners->at(i)->receive(cmd);
}

void OpenGLCommandEmitter::manageControlPressed(unsigned char key, int x, int y)
{
	for (int i = 0; i < COMMANDS; i++)
		if (key == commands[i])
			this->emit(i);
}

void OpenGLCommandEmitter::manageControlReleased(unsigned char key, int x, int y)
{
	this->manageControlPressed(key, x, y);
}

OpenGLCommandEmitter::~OpenGLCommandEmitter()
{
}
