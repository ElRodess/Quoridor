
main : main.o graphics.o affichage.o jouer.o enregistrer.o
	gcc -Wall -o main main.o graphics.o affichage.o jouer.o enregistrer.o `sdl-config --libs` -lSDL_ttf -lm

run : main
	./main

clear : 
	rm *.o

main.o : main.c jouer.h affichage.h enregistrer.h graphics.h 
	gcc -c -Wall main.c 

affichage.o : affichage.c graphics.h
	gcc -c -Wall affichage.c

jouer.o : jouer.c affichage.h enregistrer.h graphics.h 
	gcc -c -Wall jouer.c

enregistrer.o : enregistrer.c affichage.h jouer.h graphics.h
	gcc -c -Wall enregistrer.c

#construit le fichier binaire graphics.o
graphics.o: graphics.c graphics.h
	rm -f police.h
	touch police.h
	if test -e /usr/include/SDL_ttf.h;           then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/include/SDL/SDL_ttf.h;       then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL_ttf.h;     then echo "#define SDL_TTF_OK" > police.h; fi
	if test -e /usr/local/include/SDL/SDL_ttf.h; then echo "#define SDL_TTF_OK" > police.h; fi
	gcc -Wall `sdl-config --cflags`  -c graphics.c

