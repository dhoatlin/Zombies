/*
* Header for display.c
*/

#define MOVE_TIME 20

#define ROOM_SIZE 300

void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void drawRoom();
void drawBullets();
void drawZombies();
void moveObjects();
void movePlayer();
void moveBullets();
void moveZombies();
