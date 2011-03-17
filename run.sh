clear
rm camera.o
rm display.o
rm bullet.o
rm zombie.o
rm zombies
gcc -c display.c camera.c bullet.c zombie.c
gcc -o zombies -lGL -lGLU -lglut camera.o display.o bullet.o
./zombies
