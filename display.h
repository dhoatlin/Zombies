/*
* Header for display.c
*/

#define MOVE_TIME 20
#define MAX_ZOMBIES 25

void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void drawRoom();
void drawBullets();
void moveObjects();
void movePlayer();
void moveBullets();
