#pragma once
#include "OpenGLView.h"

OpenGLView::OpenGLView()
{
	this->emitter = new OpenGLCommandEmitter();

	int argc = 0;
	char * argv = NULL;
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Game Loop Demo");
	viewInstance = this;
	glutDisplayFunc(drawSceneCallback);
	//glutMouseFunc(mouseClick);
	glutReshapeFunc(resizeCallback);
	glutKeyboardFunc(manageControlPressedCallback);
	glutSetKeyRepeat(0);
	glutKeyboardUpFunc(manageControlReleasedCallback);
	//glutPassiveMotionFunc(mouseMotion);
}

void OpenGLView::drawScene()
{
	glutSwapBuffers();
	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLView::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLView::manageControlPressed(unsigned char key, int x, int y)
{
	this->emitter->manageControlPressed(key, x, y);
}

void OpenGLView::manageControlReleased(unsigned char key, int x, int y)
{
	this->emitter->manageControlReleased(key, x, y);
}

void OpenGLView::startGameLoop(Presenter * presenter)
{
	presenterInstance = presenter;
	this->emitter->sub(presenter);
	glutTimerFunc(FRAMETIME, gameLoopCallback, 0);
	glutMainLoop();
}

void OpenGLView::drawCircle(float x, float y, float radius)
{
	x += SCREEN_WIDTH / 2;
	y += SCREEN_HEIGHT / 2;
	glPushMatrix();
	/*glTranslatef(this->currentInWorldPosition.x, this->currentInWorldPosition.y, 0.0);
	glScalef(scale, scale, 1.0);*/

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	float twicepi = 2 * 3.142;
	glBegin(GL_POLYGON);
	for (float a = 0; a < twicepi; a += twicepi / 20)
		glVertex2d(x + radius * cos(a), y + radius * sin(a));
	glEnd();
	glPopMatrix();
}

OpenGLView::~OpenGLView()
{
}

// Callback functions

void drawSceneCallback()
{
	viewInstance->drawScene();
}

void resizeCallback(int w, int h)
{
	viewInstance->resize(w, h);
}

void gameLoopCallback(int value)
{
	presenterInstance->gameLoop();
	glutTimerFunc(FRAMETIME, gameLoopCallback, 0);
}

void manageControlPressedCallback(unsigned char key, int x, int y)
{
	viewInstance->manageControlPressed(key, x, y);
}

void manageControlReleasedCallback(unsigned char key, int x, int y)
{
	viewInstance->manageControlReleased(key, x, y);
}

