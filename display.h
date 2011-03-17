/*
* Header for display.c
*/

#define MOVE_TIME 20

void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void drawRoom();
void moveObjects();
void movePlayer();
