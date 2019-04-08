#pragma once
#include "View.h"
#include "Presenter.h"
#include "OpenGLCommandEmitter.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FRAMETIME 0

class OpenGLView : 
	public View
{
private:
	OpenGLCommandEmitter * emitter;
public:
	OpenGLView();
	virtual void drawScene();
	virtual void resize(int w, int h);
	virtual void manageControlPressed(unsigned char key, int x, int y);
	virtual void manageControlReleased(unsigned char key, int x, int y);
	virtual void startGameLoop(Presenter * presenter);
	virtual void drawCircle(float x, float y, float radius);
	~OpenGLView();
};

extern "C"
static OpenGLView * viewInstance;
static Presenter * presenterInstance;
void drawSceneCallback();
void resizeCallback(int w, int h);
void gameLoopCallback(int value);
void manageControlPressedCallback(unsigned char key, int x, int y);
void manageControlReleasedCallback(unsigned char key, int x, int y);
