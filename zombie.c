/*
* Handles zomebie creation, movement, and destruction
*/

//heading = tan(theta) opposite/adjacent
//atan(xdif/zdif);


#include "zombie.h"
#include <math.h>

Zombie spawnZombie(double zSpeed, double* zlocation, double zhealth)
{
	Zombie zombie;
	
	zombie.alive = 1;
	zombie.speed = zSpeed;
	zombie.heading = 0;
	zombie.location[0] = zlocation[0];
	zombie.location[1] = zlocation[1];
	zombie.location[2] = zlocation[2];
	
	zombies[zombieIndex] = zombie;
	zombieIndex = (zombieIndex + 1) % MAX_ZOMBIES;
}

void updateZombieHeadings(double* pLocation)
{
	int i;
	double xdif, zdif;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			xdif = abs(pLocation[0] - zombies[i].location[0]);
			zdif = abs(pLocation[2] - zombies[i].location[2]);
			zombies[i].heading = atan(xdif/zdif);
		}
	}
}

void moveZombies(int id)
{
	zombies[id].location[0] += sin(zombies[id].heading) * zombies[id].speed;
	zombies[id].location[2] -= cos(zombies[id].heading) * zombies[id].speed;
}
