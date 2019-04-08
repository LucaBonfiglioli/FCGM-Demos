#pragma once
class Presenter;

class View
{
public:
	virtual void startGameLoop(Presenter * presenter) = 0;
	virtual void drawCircle(float x, float y, float radius) = 0;
	virtual void drawScene() = 0;
	~View();
};

