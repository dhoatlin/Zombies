clear
rm camera.o
rm display.o
rm bullet.o
rm zombies
gcc -c display.c camera.c bullet.c
gcc -o zombies -lGL -lGLU -lglut camera.o display.o bullet.o
./zombies
