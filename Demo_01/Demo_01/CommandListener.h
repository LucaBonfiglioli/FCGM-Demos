#pragma once

typedef int Command;

#define FORWARD 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define RESET 4
#define TOGGLE_DAMPENERS 5

#define COMMANDS 6

const unsigned char commands[COMMANDS] =
{
	'w', // FORWARD
	's', // BACK
	'a', // LEFT
	'd', // RIGHT
	'n', // RESET
	'e' // TOGGLE_DAMPENERS
};

const bool singleHit[COMMANDS] =
{
	false, // FORWARD
	false, // BACK
	false, // LEFT
	false, // RIGHT
	true, // RESET
	true // TOGGLE_DAMPENERS
};

class CommandListener
{
public:
	virtual void receive(Command cmd) = 0;
	~CommandListener();
};

