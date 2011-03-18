/*
* Header for zombie.c
*/

#define MAX_ZOMBIES 100

typedef struct
{
	double health;
	
	double heading, speed;
	
	int alive;
	
	double location[3];
} Zombie;

int zombieIndex = 0;
Zombie zombies[MAX_ZOMBIES];

void createZombie(double pSpeed, double pHeading, double* plocation, double phealth);
void updateHeadings(double* pLocation);

