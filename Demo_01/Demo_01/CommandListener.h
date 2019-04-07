#pragma once

typedef int Command;

#define FORWARD 0
#define BACK 1
#define LEFT 2
#define RIGHT 3

#define COMMANDS 4

const unsigned char commands[COMMANDS] =
{
	'w',
	's',
	'a',
	'd'
};

class CommandListener
{
public:
	virtual void receive(Command cmd) = 0;
	~CommandListener();
};

