
#include <windows.h> 
#include "gl/glut.h"
#include <stdio.h>
#include <math.h>
#include "Scene.h"
#include "Camera.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define SCREEN_Xo		100
#define SCREEN_Yo		100
#define FULLSCREEN		0

Timer timer;
float tick;
bool keys[256];
int  mousex,mousey;

Scene* pScene;

bool GameInit(void)
{
	Camera::get()->Init(SCREEN_WIDTH,SCREEN_HEIGHT,6);

	pScene = new Scene();
	if(!pScene->Init()) return false;

	// setup scene lighting
	GLfloat ambient0[]= { 1, 1, 1, 1.0 };
	GLfloat diffuse0[]= { 1.0, 1.0, 1.0, 1.0 };
	GLfloat ambient1[]= { 0, 0, 0, 1.0 };
	GLfloat diffuse1[]= { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);

	mousex = SCREEN_WIDTH  >> 1;
	mousey = SCREEN_HEIGHT >> 1;

	return true;
}

void GameLogic()   
{
	pScene->Logic(tick, keys);
}

void GameRender()   
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Camera::get()->Update(keys,mousex,mousey,tick);
	Camera::get()->Look();

	glPushMatrix();
		GLfloat posl0[]= { -1.0, 1.0, -1.0 , 0.0};
		GLfloat posl1[]= { 1.0, 1.0, 1.0 , 0.0};
		glLightfv(GL_LIGHT0, GL_POSITION, posl0);
		glLightfv(GL_LIGHT1, GL_POSITION, posl1);
	glPopMatrix();

	pScene->Render(tick);

    glutSwapBuffers();
}

void GameReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (float)w/(float)h, 0.1, 10000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:	exit(0);									break;
		case 'S':
		case 's':	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);	break;
		case 'W':
		case 'w':	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);	break;
		case 'P':
		case 'p':	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);	break;
		default:	keys[key] = true;
	}
}

void GameSpecialKeys(int key, int x, int y)
{
	keys[key] = true;
}

void GameSpecialKeysUp(int key, int x, int y)
{
	keys[key] = false;
}

void GameMouse(int x, int y)
{
	mousex = x;
	mousey = y;
}

void GameLoop()
{
	if(FULLSCREEN)	SetCursorPos(SCREEN_WIDTH>>1,SCREEN_HEIGHT>>1);
	else			SetCursorPos(SCREEN_Xo+(SCREEN_WIDTH>>1),SCREEN_Yo+(SCREEN_HEIGHT>>1));

	tick=timer.tick();
	if(tick>1.0f/50.0f) tick=1.0f/25.0f;

	GameLogic();
	GameRender();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
	if(FULLSCREEN)
	{
		char s[16];
		glutGameModeString(s);
		glutEnterGameMode();
	}
	else
	{
		glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
		glutInitWindowPosition(SCREEN_Xo,SCREEN_Yo);
		glutCreateWindow("Master en Disseny i Creació de Videojocs - UPC School");
	}

	glutSetCursor(GLUT_CURSOR_NONE);
	GameInit();
	glutDisplayFunc(GameRender);
	glutReshapeFunc(GameReshape);
	glutKeyboardFunc(GameKeyboard);
	glutSpecialFunc(GameSpecialKeys);
	glutSpecialUpFunc(GameSpecialKeysUp);
	glutPassiveMotionFunc(GameMouse);
	glutIdleFunc(GameLoop);
	glutMainLoop();

	delete pScene;
}
