/*
* Header class for bullet.c
*/

typedef struct
{
	double heading, speed;
	
	int alive;
	
	double location[3];
	
} Bullet;

Bullet createBullet(double pSpeed, double pHeading, double* plocation);
Bullet moveBullet(Bullet bullet);
Bullet checkAlive(Bullet bullet);
