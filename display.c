/*
* Handles all the openGL stuff to display images
*
* Main method is also here
*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "camera.h"
#include "display.h"
#include "bullet.h"
#include "zombie.h"

int count = 0;
int keyPressed[256]; //holds key states for movement purposes

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glLineWidth(2.0);
   glutIgnoreKeyRepeat(1);
   printf ("just setting up the test scene\n");
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
}


void keyboard(unsigned char key, int x, int y)
{
	double* location;
	double bulletLoc[3];
	double heading;
	switch (key) {
		case 27:
			exit(0);
			break;
		case ' ':
			//draw bullet here
			location = getCameraLoc(); //bullet starts at camera
			bulletLoc[0] = location[0];
			bulletLoc[1] = location[1];
			bulletLoc[2] = location[2];
			heading = getCameraHeading(); // bullet shoots in the direction we are looking
			createZombie(1, bulletLoc, 100);
			bulletLoc[1] -= 2; //lower the bullet hieght a little
			createBullet(5, heading, bulletLoc);
			
			//drawing zombie on space for now
			
			
			break;
		default:
			break;
	}
	keyPressed[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
	keyPressed[key] = 0;
}

void moveObjects()
{
	movePlayer();
	moveBullets();
	moveZombies();
	display();
	glutTimerFunc(MOVE_TIME, moveObjects, 0);
}

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

void moveBullets()
{
	int i;
	for(i = 0; i < MAX_BULLETS; i++)
	{
		if(bullets[i].alive == 1)
			moveBullet(i);
	}
}

void moveZombies()
{
	int i;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			moveZombie(i);
		}
	}
}
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

int main(int argc, char **argv)
{
	initCamera();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("Zombie Survival");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(MOVE_TIME, moveObjects, 0);
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	return 0;
}
