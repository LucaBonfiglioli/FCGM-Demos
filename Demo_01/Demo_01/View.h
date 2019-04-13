#pragma once

#include "commons.h"

class Presenter;

class View
{
public:
	virtual void startGameLoop(Presenter * presenter) = 0;
	virtual void drawCircle(float x, float y, float radius, color4f color) = 0;
	virtual void drawAnnulus(float x, float y, float outerRad, float innerRad, color4f color) = 0;
	virtual void drawScene() = 0;
	~View();
};

