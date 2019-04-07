#pragma once
#include <iostream>
#include "Presenter.h"

int main(int argc, char * argv[]) 
{
	Presenter * p = new Presenter();
	p->startGameLoop();

	system("PAUSE");
	return 0;
}