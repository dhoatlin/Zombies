clear
rm camera.o
rm display.o
rm zombies
gcc -c display.c camera.c
gcc -o zombies -lGL -lGLU -lglut camera.o display.o
./zombies
