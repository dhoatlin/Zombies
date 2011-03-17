/*
* Handles bullet movements
*/

#include <math.h>
#include "bullet.h"

Bullet createBullet(double pSpeed, double pHeading, double* plocation)
{
	Bullet bullet = {pSpeed, pHeading, plocation};
	bullet.alive = 1;
	return bullet;
}

Bullet moveBullet(Bullet bullet)
{
	bullet.location[0] += sin(bullet.heading) * bullet.speed;
	bullet.location[2] -= cos(bullet.heading) * bullet.speed;
	//if(bullet.location[0] > 50 || bullet.location[0] < 50)
	//{
	//	bullet.alive = 0;
	//}
	//if(bullet.location[2] > 50 || bullet.location[2] < 50)
	//{
	//	bullet.alive = 0;
	//}	
	
	return bullet;
}
