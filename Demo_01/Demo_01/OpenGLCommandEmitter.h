#pragma once
#include <vector>
#include "CommandEmitter.h"

class OpenGLCommandEmitter : 
	public CommandEmitter
{
private:
	std::vector<CommandListener*> * listeners;
public:
	OpenGLCommandEmitter();
	virtual void sub(CommandListener * listener);
	virtual void unsub(CommandListener * listener);
	virtual void emit(Command cmd);
	virtual void manageControlPressed(unsigned char key, int x, int y);
	virtual void manageControlReleased(unsigned char key, int x, int y);
	~OpenGLCommandEmitter();
};

