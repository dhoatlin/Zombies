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

int count = 0;

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glLineWidth(2.0);
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

	glColor3f(1.0, 0.0, 1.0);
   
	//draw
	glTranslatef(0.0, 5.0, -10.0);  // position in frustum
	//glScalef(1.0, 2.0, 1.0);        // elongate cube
	glutWireCube(20.0); //cube 1
	glPushMatrix();
	glTranslatef(5.0, 0.0, 3.0);
	glutWireCube(10.0); //cube 2
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.0, 0.0, -3.0);   // move sphere to top of cube
	glutWireCube(5.0); //cube 3
	glPopMatrix();
	
	glFlush();
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	  case 'w':
		  moveForward();
		  display();
		  break;
	  case 'a':
		  lookLeft();
		  display();
		  break;
	  case 's':
		  backUp();
		  display();
		  break;
	  case 'd':
		  lookRight();
		  display();
		  break;
      default:
         break;
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
	glEnable(GL_DEPTH_TEST);
	
	glutMainLoop();
	return 0;
}
