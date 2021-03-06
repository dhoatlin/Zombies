/*
* Moves the players vision around
*/

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "camera.h"
#include "display.h"

Camera camera;

void initCamera()
{
	//how far the player can walk with one key press
	camera.speed = 2.0;

	//The direction the player is facing
	camera.heading = 0.0;

	//storing the location of the camera AKA the player's head
	camera.location[0] = 0.0;
	camera.location[1] = 5.0; //five units high should never change
	camera.location[2] = 5.0;

	//where the camera is looking AKA the player's eyes.
	camera.direction[0] = 0.0;
	camera.direction[1] = 5.0; //looking straight forward should never change
	camera.direction[2] = 0.0;
}

//return array containing camera location
double* getCameraLoc()
{
	return camera.location;
}

//return array containing where camera is looking
double* getCameraLook()
{
	return camera.direction;
}

double getCameraHeading()
{
	return camera.heading;
}

//original strafe functions
//currently not used
//need to change the math
void strafeLeft()
{
	camera.location[0] -= camera.speed;
	camera.direction[0] -= camera.speed;
}

//original strafe functions
//currently not used
//need to change the math
void strafeRight()
{
	camera.location[0] += camera.speed;
	camera.direction[0] += camera.speed;
}

//rotate camera to the left
void lookLeft()
{
	//move heading 1 degree to the left
	camera.heading -= (PI / 90.0);
	if(camera.heading < 0.0) //heading is back at origin
	{
		camera.heading = PI*2.0;
	}
	computeDirection();
}

//rotate camera to the right
void lookRight()
{
	camera.heading += PI / 90.0;
	if(camera.heading > PI*2.0) //heading is back at origin
	{
		camera.heading = 0.0;
	}
	
	checkBounds();
	
	computeDirection();
}

//take a step back
void backUp()
{
	camera.location[0] -= sin(camera.heading) * camera.speed;
	camera.location[2] += cos(camera.heading) * camera.speed;

	//checking if the move is possible
	checkBounds();
	
	computeDirection();
}

//take a step forward
void moveForward()
{
	camera.location[0] += sin(camera.heading) * camera.speed;
	camera.location[2] -= cos(camera.heading) * camera.speed;
	
	computeDirection();
}

//calculate the direction we are looking
void computeDirection()
{
	camera.direction[0] = camera.location[0] + sin(camera.heading);
	camera.direction[2] = camera.location[2] - cos(camera.heading);
}

//keeping the camera inside the room
void checkBounds()
{
	if(camera.location[0] < (ROOM_SIZE * -1 + PLAYER_SPACING))
		camera.location[0] = (ROOM_SIZE * -1 + PLAYER_SPACING);
	else if(camera.location[0] > ROOM_SIZE - PLAYER_SPACING)
		camera.location[0] = ROOM_SIZE - PLAYER_SPACING;
		
	if(camera.location[2] < (ROOM_SIZE * -1 + PLAYER_SPACING))
		camera.location[2] = (ROOM_SIZE * -1 + PLAYER_SPACING);
	else if(camera.location[2] > ROOM_SIZE - PLAYER_SPACING)
		camera.location[2] = ROOM_SIZE - PLAYER_SPACING;
}

//printing the camera coords to the console
void printCam()
{
	int i;
	for(i = 0; i<3; i++)
	{
		printf("cameraLoc: %f\n", camera.location[i]);
	}
	printf("\n");
	for(i = 0; i<3; i++)
	{
		printf("cameraLook: %f\n", camera.direction[i]);
	}
	printf("\n-----------\n");
}
