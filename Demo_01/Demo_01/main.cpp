#pragma once
#include <iostream>
#include "Presenter.h"
#include <ctime>
#include <random>

int main(int argc, char * argv[]) 
{
	srand(time(0));
	Presenter * p = new Presenter();
	p->startGameLoop();

	system("PAUSE");
	return 0;
}