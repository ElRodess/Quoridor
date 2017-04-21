#include "graphics.h"
#include "affichage.h"
#include "enregistrer.h"
#include "jouer.h"
#include <stdio.h>
#include <stdlib.h>
////////
//MAIN//
////////

int main()
{
init_graphics(650,449);
GAME g;
Liste l = NULL;
g = initialisation();
l = AjoutDebut(l,g);
affiche_auto_off();
fill_screen(blanc);
affichage(g);
affiche_joueur(g);
affiche_retour(l);
while(1)
{
affiche_all();
l = jouer(l->tour,(l->tour).joueur,l);
g = l->tour;
affiche_joueur(g);
affiche_retour(l);
affichage(g);
Victoire(l,g);
}
}
