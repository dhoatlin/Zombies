/*
* Handles zomebie creation, movement, and destruction
*/

#include "zombie.h"
#include <math.h>
#include "display.h"
#include "camera.h"

int zombieIndex = 0;

//create a zombie and store it in the zombies container
void createZombie(double zSpeed, double* zlocation, double zhealth)
{
	printf("zombie added\n");
	Zombie zombie;
	
	zombie.alive = 1;
	zombie.health = zhealth;
	zombie.speed = zSpeed;
	zombie.heading = 0;
	zombie.location[0] = zlocation[0];
	zombie.location[1] = zlocation[1];
	zombie.location[2] = zlocation[2];
	
	zombies[zombieIndex] = zombie;
	zombieIndex = (zombieIndex + 1) % MAX_ZOMBIES;
}

//trying to update the zombie heading to chase the player
//currently not working that well, but the player is chased
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
			// > <
			//finding quadrant relative to zombie
			if(xdif < 0 && zdif < 0) //Q1
			{
				//printf("quad1\n");
				zombies[i].heading = -1 * (atan(absZ/absX));
			}
			else if(xdif < 0 && zdif > 0) //Q2
			{
				//printf("quad2\n");
				zombies[i].heading = -1 * (atan(absX/absZ) + (PI/2));
			}
			else if(xdif > 0 && zdif > 0) //Q3
			{
				//printf("quad3\n");
				zombies[i].heading = -1 * (atan(absZ/absX) + PI);
			}
			else if(xdif > 0 && zdif < 0) //Q4
			{
				//printf("quad4\n");
				zombies[i].heading = -1 * (atan(absX/absZ) + (3*PI/2));
			}
			else
			{
				//if none are true then continue original heading
			}
		}
	}
}

//move the zombie according to its heading
//for now i just destroy it if it makes it to a wall
void moveZombie(int id)
{
	zombies[id].location[0] += sin(zombies[id].heading) * zombies[id].speed;
	zombies[id].location[2] -= cos(zombies[id].heading) * zombies[id].speed;
	
	if(zombies[id].location[0] > ROOM_SIZE || zombies[id].location[0] < (ROOM_SIZE * -1))
	{
		zombies[id].alive = 0;
	}
	if(zombies[id].location[2] > ROOM_SIZE || zombies[id].location[2] < (ROOM_SIZE * -1))
	{
		zombies[id].alive = 0;
	}
}

//decrease health if the zombie is hit
void zombieDamage(int id)
{
	zombies[id].health -= 1;
	//if dead
	if(zombies[id].health < 1)
	{
		zombies[id].alive = 0;
	}
}
