/*
* Header class for bullet.c
*/

typedef struct
{
	double heading, speed;
	
	int alive;
	
	double location[3];
	
} Bullet;


#define MAX_BULLETS 100

Bullet bullets[MAX_BULLETS];


void createBullet(double pSpeed, double pHeading, double* pLocation);
void moveBullet(int id);
