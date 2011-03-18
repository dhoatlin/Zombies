/*
* Handles all the openGL stuff to display images
*
* This also calls a lot of the game logic functions. Pretty much everything
* happens here.
*
* Main method is also here
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "camera.h"
#include "display.h"
#include "bullet.h"
#include "zombie.h"

int count = 0;
int keyPressed[256]; //holds key states for movement purposes

int mainWindow, radar;
int killCount = 0;

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glLineWidth(2.0);
   glutIgnoreKeyRepeat(1);
}


void reshape(int w, int h)
{
   glViewport(0, 0, w, h);

   //perspective view
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity();
   gluPerspective(50, w / h, 1.0, 1000.0);

   glMatrixMode(GL_MODELVIEW);
}


void display(void)
{
	glutSetWindow(mainWindow);
	double* cameraLoc = getCameraLoc();
	double* cameraLook = getCameraLook();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(
		cameraLoc[0], cameraLoc[1], cameraLoc[2],
		cameraLook[0], cameraLook[1], cameraLook[2],
		0,1,0);

	//draw
	drawRoom();
	drawBullets();
	drawZombies();
		

	glFlush();
	renderRadar();
}

//trying to make radar, but not rendering at all
void renderRadar()
{
	glutSetWindow(radar);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glLoadIdentity();
	double* location = getCameraLoc();
	gluLookAt(location[0], 14, location[2], location[0], location[1], location[2], 0, 1, 0);
	glFlush();
}

//handling all the keypresses
void keyboard(unsigned char key, int x, int y)
{
	double* location;
	double bulletLoc[3];
	double randLoc[3];
	double heading;
	switch (key) {
		case 27:
			printf("kills: %d\n", killCount);
			exit(0);
			break;
		case ' ':
			//draw bullet here
			location = getCameraLoc(); //bullet starts at camera
			bulletLoc[0] = location[0];
			bulletLoc[1] = location[1];
			bulletLoc[2] = location[2];
			heading = getCameraHeading(); // bullet shoots in the direction we are looking
			bulletLoc[1] -= 2; //lower the bullet height a little
			createBullet(5, heading, bulletLoc);			
			break;
		//spawn zombie on 'z'
		case 'z':
			randLoc[0] = (rand() % (ROOM_SIZE * 2)) - ROOM_SIZE;
			randLoc[1] = 3;
			randLoc[2] = (rand() % (ROOM_SIZE * 2)) - ROOM_SIZE;
			createZombie(.7, randLoc, 5);
			break;
		default:
			break;
	}
	//storing this key as pressed
	keyPressed[key] = 1;
}

//reseting the key pressed to 0
void keyUp(unsigned char key, int x, int y)
{
	keyPressed[key] = 0;
}

//move all the objects in the game around
void moveObjects()
{
	movePlayer();
	moveBullets();
	moveZombies();
	checkBulletHit();
	display();
	glutTimerFunc(MOVE_TIME, moveObjects, 0);
}

//calling the camera functions to move around playing area
void movePlayer()
{
	if(keyPressed['w'] == 1)
		moveForward();
	if(keyPressed['a'] == 1)
		lookLeft();
	if(keyPressed['s'] == 1)
		backUp();
	if(keyPressed['d'] == 1)
		lookRight();
}

//move all the bullets
void moveBullets()
{
	int i;
	for(i = 0; i < MAX_BULLETS; i++)
	{
		if(bullets[i].alive == 1)
			moveBullet(i);
	}
}

//trying to move zombies toward player, kind of working but only by chance.
//currently zombies move in a direction(not really towards the player) until 
//they get to an axis. 
//
//when a zombie reaches an axis its heading bounces back and forth. it just so
//happens that the result is towards the player.
void moveZombies()
{

	int i;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			moveZombie(i);
		}
		//else //zombie at this point is dead, make a new one
		//{
		//	double randLoc[3];
		//	randLoc[0] = (rand() % (ROOM_SIZE * 2)) - ROOM_SIZE;
		//	randLoc[1] = 3;
		//	randLoc[2] = (rand() % (ROOM_SIZE * 2)) - ROOM_SIZE;
		//	createZombie(.7, randLoc, 5);
		//}
	}
	//update the direction of the zombies after moving
	updateZombieHeadings(getCameraLoc());	
}

//draw the room
void drawRoom()
{
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	/* Floor */
	glVertex3f((ROOM_SIZE * -1),-1,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,-1,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,-1,ROOM_SIZE);
	glVertex3f((ROOM_SIZE * -1),-1,ROOM_SIZE);
	glColor3f(1.0, 0.0, 0.0);
	/* Ceiling */
	glVertex3f((ROOM_SIZE * -1),15,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,15,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,15,ROOM_SIZE);
	glVertex3f((ROOM_SIZE * -1),15,ROOM_SIZE);
	
	/* Walls */
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f((ROOM_SIZE * -1),-1,ROOM_SIZE);
	glVertex3f(ROOM_SIZE,-1,ROOM_SIZE);
	glVertex3f(ROOM_SIZE,15,ROOM_SIZE);
	glVertex3f((ROOM_SIZE * -1),15,ROOM_SIZE);
	
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f((ROOM_SIZE * -1),-1,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,-1,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,15,(ROOM_SIZE * -1));
	glVertex3f((ROOM_SIZE * -1),15,(ROOM_SIZE * -1));
	
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(ROOM_SIZE,15,ROOM_SIZE);
	glVertex3f(ROOM_SIZE,-1,ROOM_SIZE);
	glVertex3f(ROOM_SIZE,-1,(ROOM_SIZE * -1));
	glVertex3f(ROOM_SIZE,15,(ROOM_SIZE * -1));
	
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f((ROOM_SIZE * -1),15,ROOM_SIZE);
	glVertex3f((ROOM_SIZE * -1),-1,ROOM_SIZE);
	glVertex3f((ROOM_SIZE * -1),-1,(ROOM_SIZE * -1));
	glVertex3f((ROOM_SIZE * -1),15,(ROOM_SIZE * -1));
	glEnd();
}

//draw all the bullets
void drawBullets()
{
	int i;
	for(i = 0; i < MAX_BULLETS; i++)
	{
		//only  draw if bullet is 'alive'
		if(bullets[i].alive == 1)
		{
			//printf("drawing bullet again: %d\n", i);
			glPushMatrix();
			//translate to bullet position
			//printf("%f, %f, %f\n", bullets[i].location[0], bullets[i].location[1], bullets[i].location[2]);
			glTranslatef(bullets[i].location[0], bullets[i].location[1], bullets[i].location[2]);
			glColor3f(1.0,1.0,1.0);
			glutSolidSphere(.1, 5, 5);
			glPopMatrix();
		}		
	}
}

//draw all the zombies. Would have liked to make arms/legs but spent too much
//time on game logic. Currently zombies are just rendered as boxes
void drawZombies()
{
	int i;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			glPushMatrix();
			glTranslatef(zombies[i].location[0], zombies[i].location[1], zombies[i].location[2]);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidCube(3);
			glPopMatrix();
		}
	}
}

//collision detection for bullets and zombies
void checkBulletHit()
{
	int i, j;
	double xDifSq, zDifSq, distance;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			for(j = 0; j < MAX_BULLETS; j++)
			{
				if(bullets[j].alive == 1)
				{
					distance = distanceSq(zombies[i].location[0], zombies[i].location[2], bullets[j].location[0], bullets[j].location[2]);
					if(distance < 5)
					{
						//printf("hit detected\n");
						destroyBullet(j);
						killCount += zombieDamage(i); //will eventually render to screen
					}
				}
			}
		}
	}
}

//just calculating the distance squared between two objects
double distanceSq(double x1, double y1, double x2, double y2)
{
	return pow(x1-x2, 2) + pow(y1-y2, 2);
}

int main(int argc, char **argv)
{
	initCamera();
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	mainWindow = glutCreateWindow("Zombie Survival");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(MOVE_TIME, moveObjects, 0);
	glEnable(GL_DEPTH_TEST);
	
	//setting up radar subwindow. not working correctly
	radar = glutCreateSubWindow(mainWindow, 0, 400, 100, 100);
	glutDisplayFunc(renderRadar);
	init();
	
	glutMainLoop();
	return 0;
}
