#pragma once
#include "CommandListener.h"

class CommandEmitter
{
public:
	virtual void sub(CommandListener * listener) = 0;
	virtual void unsub(CommandListener * listener) = 0;
	virtual void emit(Command cmd) = 0;
	~CommandEmitter();
};

