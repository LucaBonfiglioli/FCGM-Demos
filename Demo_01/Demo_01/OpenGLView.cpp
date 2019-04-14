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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a);
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

void OpenGLView::drawCircle(float x, float y, float radius, color4f color)
{
	x += SCREEN_WIDTH / 2;
	y += SCREEN_HEIGHT / 2;
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	float twicepi = 2 * PI;
	float step = twicepi / (BASE_CIRCLE_SEGMENTS + radius * CIRCLE_SEGMENTS_SCALING);
	glBegin(GL_POLYGON);
	for (float a = 0.0f; a < twicepi; a += step)
		glVertex2d(x + radius * cos(a), y + radius * sin(a));
	glEnd();
	glPopMatrix();
}

void OpenGLView::drawAnnulus(float x, float y, float innerRad, float outerRad, color4f color)
{
	x += SCREEN_WIDTH / 2;
	y += SCREEN_HEIGHT / 2;
	glPushMatrix();
	glColor4f(color.r, color.g, color.b, color.a);
	float twicepi = 2 * PI;
	float step = twicepi / (BASE_CIRCLE_SEGMENTS + innerRad * CIRCLE_SEGMENTS_SCALING);
	if (innerRad < 0)
		std::cout << innerRad << "\n";
	for (float a = 0.0f; a < twicepi; a += step)
	{
		if (a + step >= twicepi)
			step = twicepi - a;
		glBegin(GL_POLYGON);
		glVertex2d(x + outerRad * cos(a), y + outerRad * sin(a));
		glVertex2d(x + outerRad * cos(a + step), y + outerRad * sin(a + step));
		glVertex2d(x + innerRad * cos(a + step), y + innerRad * sin(a + step));
		glVertex2d(x + innerRad * cos(a), y + innerRad * sin(a));
		glEnd();
	}
	glPopMatrix();
}

OpenGLView::~OpenGLView()
{
}

// Callback C functions

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

