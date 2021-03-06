/*
* Handles bullet movements, creation, and destruction
*/

#include <math.h>
#include <stdio.h>
#include "display.h"
#include "bullet.h"



int bulletIndex = 0;

//create a new bullet and store in the bullets container
void createBullet(double pSpeed, double pHeading, double* pLocation)
{
	//printf("adding bullet at index %d\n", bulletIndex);
	//Bullet bullet = bullets[bulletIndex];
	//bulletIndex = (bulletIndex + 1) % MAX_BULLETS;
	
	Bullet bullet;
	
	bullet.alive = 1;
	bullet.speed = pSpeed;
	bullet.heading = pHeading;
	bullet.location[0] = pLocation[0];
	bullet.location[1] = pLocation[1];
	bullet.location[2] = pLocation[2];
	
	bullets[bulletIndex] = bullet;
	bulletIndex = (bulletIndex + 1) % MAX_BULLETS;
	
	//printf("bullet created\n");
}

//move the bullet according to its heading
void moveBullet(int id)
{
	//printf("moving bullet\n");
	bullets[id].location[0] += sin(bullets[id].heading) * bullets[id].speed;
	bullets[id].location[2] -= cos(bullets[id].heading) * bullets[id].speed;
	//printf("%f, %f\n", bullets[id].location[0], bullets[id].location[2]);
	if(bullets[id].location[0] > ROOM_SIZE || bullets[id].location[0] < (ROOM_SIZE * -1))
	{
		destroyBullet(id);
	}
	if(bullets[id].location[2] > ROOM_SIZE || bullets[id].location[2] < (ROOM_SIZE * -1))
	{
		destroyBullet(id);
	}	
}

//destroy the bullet if it leaves the room or hits a zombie
void destroyBullet(int id)
{
	bullets[id].alive = 0;
}
