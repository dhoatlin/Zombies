/*
* Header for zombie.c
*/

typedef struct
{
	double health;
	
	double heading, speed;
	
	int alive;
	
	double location[3];
} Zombie;

Zombie createZombie(double pSpeed, double pHeading, double* plocation, double phealth);

