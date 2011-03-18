/*
* Handles zomebie creation, movement, and destruction
*/

//heading = tan(theta) opposite/adjacent
//atan(xdif/zdif);


#include "zombie.h"
#include <math.h>
#include "camera.h"

int zombieIndex = 0;

void createZombie(double zSpeed, double* zlocation, double zhealth)
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
	double xdif, zdif, absX, absZ;
	for(i = 0; i < MAX_ZOMBIES; i++)
	{
		if(zombies[i].alive == 1)
		{
			xdif = pLocation[0] - zombies[i].location[0];
			zdif = pLocation[2] - zombies[i].location[2];
			absX = abs(xdif);
			absZ = abs(zdif);
			
			//finding quadrant relative to zombie
			if(xdif > 0 && zdif < 0) //Q1
			{
				zombies[i].heading = atan(absZ/absX);
			}
			else if(xdif < 0 && zdif < 0) //Q2
			{
				zombies[i].heading = atan(absX/absZ) + (PI/2);
			}
			else if(xdif < 0 && zdif > 0) //Q3
			{
				zombies[i].heading = atan(absZ/absX) + PI;
			}
			else if(xdif > 0 && zdif > 0) //Q3
			{
				zombies[i].heading = atan(absX/absZ) + (3*PI/2);
			}
			else
			{
				//if none are true then continue original heading
			}
		}
	}
}

void moveZombie(int id)
{
	zombies[id].location[0] += sin(zombies[id].heading) * zombies[id].speed;
	zombies[id].location[2] -= cos(zombies[id].heading) * zombies[id].speed;
}
