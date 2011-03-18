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


Zombie zombies[MAX_ZOMBIES];

void createZombie(double pSpeed, double* plocation, double phealth);
void moveZombie(int id);
int zombieDamage(int id);
void updateHeadings(double* pLocation);

