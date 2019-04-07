#pragma once
class Presenter;

class View
{
public:
	virtual void startGameLoop(Presenter * presenter) = 0;
	virtual void drawTriangle(float x, float y) = 0;
	virtual void drawScene() = 0;
	~View();
};

