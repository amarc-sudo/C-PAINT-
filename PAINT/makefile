#changer le nom des deux lignes suivantes si nécessaire
SOURCE = outil.o main.o  couleur.o plateau.o menu.o lettre.o
OUTPUT = c-paint
LIB = -lm -lSDL -lSDL_ttf
OPT = -Wall


SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)


all: $(OUTPUT)

clean: outil.o
	@rm outil.o 

$(OUTPUT): ../lib/libgraphique.o outil.o main.o  couleur.o plateau.o menu.o lettre.o
	@gcc   ../lib/libgraphique.o outil.o main.o  couleur.o plateau.o menu.o lettre.o -o $(OUTPUT)  $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LIB)


../lib/libgraphique.o: ../lib/libgraphique.c
	@gcc   -c ../lib/libgraphique.c -o ../lib/libgraphique.o

outil.o: outil.c
	gcc -o outil.o -c outil.c -W -Wall

main.o: main.c outil.h
	gcc -o main.o -c main.c -W -Wall

couleur.o: couleur.c
	gcc -o couleur.o -c couleur.c -W -Wall

plateau.o: plateau.c
	gcc -o plateau.o -c plateau.c -W -Wall

menu.o: menu.c
	gcc -o menu.o -c menu.c -W -Wall

lettre.o: lettre.c
		gcc -o lettre.o -c lettre.c -W -Wall
