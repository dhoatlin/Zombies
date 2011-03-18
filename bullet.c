/*
* Handles bullet movements
*/

#include <math.h>
#include <stdio.h>
#include "bullet.h"

int bulletIndex = 0;

void createBullet(double pSpeed, double pHeading, double* pLocation)
{
	printf("adding bullet at index %d\n", bulletIndex);
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

void moveBullet(int id)
{
	//printf("moving bullet\n");
	bullets[id].location[0] += sin(bullets[id].heading) * bullets[id].speed;
	bullets[id].location[2] -= cos(bullets[id].heading) * bullets[id].speed;
	printf("%f, %f\n", bullets[id].location[0], bullets[id].location[2]);
	if(bullets[id].location[0] > 50 || bullets[id].location[0] < -50)
	{
		bullets[id].alive = 0;
	}
	if(bullets[id].location[2] > 50 || bullets[id].location[2] < -50)
	{
		bullets[id].alive = 0;
	}	
}
