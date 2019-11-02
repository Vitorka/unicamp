all: gui susy

gui:
	gcc core.c main_gui.c timer.c physics.c entities.c list.c quadtree.c -o main_gui -pedantic -std=c99 -lm -Wall -g -D RENDER_SIMULATION_FLAG -lSDL2 -lSDL2_image

susy:
	gcc main.c physics.c entities.c list.c quadtree.c -o main_susy -pedantic -std=c99 -Wall -g -lm
