/*
* Header for camera.c
*/

#define PI 3.14159265
#define PLAYER_SPACING 5

typedef struct
{
	//speed of camera movement
	double speed;
	
	//location and look direction of camera
	double location[3];
	double direction[3];
	
	//degree value of where the camera is looking
	//maybe it should be radians?
	double heading;
} Camera;

double* getCameraLoc();
double* getCameraLook();
double getCameraHeading();
void update();
void printCam();
void strafeLeft();
void strafeRight();
void lookLeft();
void lookRight();
void backUp();
void moveForward();
void getCoords();
void computeDirection();
void checkBounds();
