#include "affichage.h"
#include "graphics.h"
#include "jouer.h"
#include <stdio.h>
#include <stdlib.h>


Liste AjoutDebut(Liste l,GAME g)
{
	Liste new = malloc(sizeof (Element));
	new->tour = g;
	new->suiv = l;
	return(new);
}

Liste SuppDebut(Liste l)
{
	Liste tmp;
	if((l== NULL )|| (l->suiv ==NULL)) return(l);
	else
	{
		tmp = l->suiv;
		free(l);
		return(tmp);
	}
}

void vider_Liste(Liste l)
{
	while( l->suiv != NULL)
	{
		l = SuppDebut(l);
	}
	free(l);
}

void Save(GAME g) 
{
	 FILE * Save = fopen("Save.txt", "w"); 
	 fwrite(&g,sizeof(GAME),1,Save); 
	 fclose(Save); 
} 

GAME Load() 
{ 
GAME g; 
FILE * Save = fopen("Save.txt", "r"); 
fread(&g,sizeof(GAME),1,Save); 
fclose(Save); 
return g; 
}
