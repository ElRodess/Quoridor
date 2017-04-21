#include "graphics.h"
//////////////
//Affichages//
//////////////
struct cases
{
int val; //Valeur de la case
int Mhaut; //Valeur du mur du haut
int Mbas;//Valeur du mur du bas
int Mdroite;//Valeur du mur de droite
int Mgauche;//Valeur du mur de gauche
};

struct game
{
struct cases T[9][9];
int Pos[2][2];
int M1;
int M2;
int joueur;
};

struct element{
  struct game tour;
  struct element* suiv;
};

typedef struct element Element;

typedef Element* Liste;

typedef struct cases CASES;
typedef struct game GAME;
//////////////////////////
#define J1 1 
#define J2 -1 
#define VIDE 0
#define ACCES 5
//////////////////////////
void affiche_bas(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50;
	P2.x=i*50+50;P2.y= j*50 +5;
	if(c.Mbas == 1) draw_fill_rectangle(P1,P2,noir);
}

void efface_bas(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50;
	P2.x=i*50+50;P2.y= j*50 +4;
	if(c.Mbas == 0) draw_fill_rectangle(P1,P2,blanc);
}
void affiche_haut(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50+ 45;
	P2.x=i*50+50;P2.y= j*50 +50;
	if(c.Mhaut == 1) draw_fill_rectangle(P1,P2,noir);
}

void efface_haut(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50+ 46;
	P2.x=i*50+50;P2.y= j*50 +50;
	if(c.Mhaut == 0) draw_fill_rectangle(P1,P2,blanc);
}
void affiche_gauche(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50;
	P2.x=i*50+5;P2.y= j*50 +50;
	if(c.Mgauche == 1) draw_fill_rectangle(P1,P2,noir);	
}

void efface_gauche(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50;P1.y=j*50;
	P2.x=i*50+4;P2.y= j*50 +50;
	if(c.Mgauche == 0) draw_fill_rectangle(P1,P2,blanc);	
}

void affiche_droite(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50+45;P1.y=j*50;
	P2.x=i*50+50;P2.y= j*50 +50;
	if(c.Mdroite == 1) draw_fill_rectangle(P1,P2,noir);
}

void efface_droite(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50+46;P1.y=j*50;
	P2.x=i*50+50;P2.y= j*50 +50;
	if(c.Mdroite == 0) draw_fill_rectangle(P1,P2,blanc);
}

void affiche_case(int i,int j,CASES c)
{
	POINT P1,P2;
	P1.x=i*50+5;P1.y=j*50+5;
	P2.x=i*50+45;P2.y= j*50 +45;
	if(c.val == ACCES) draw_rectangle(P1,P2,vert);
	if(c.val <= 1)
	{
		draw_rectangle(P1,P2,noir);
		P1.x = P1.x + 20; P1.y = P1.y + 20;
		if(c.val == J1) draw_fill_circle(P1,15,rouge);
		if(c.val == J2) draw_fill_circle(P1,15,bleu);
		if(c.val ==0) draw_fill_circle(P1,15,blanc);
    }
 
	 affiche_all();
}

void murs(int i,int j,CASES c)
{
	        efface_bas(i,j,c);
	        efface_droite(i,j,c);
	        efface_haut(i,j,c);
	        efface_gauche(i,j,c);
	        affiche_bas(i,j,c);
	        affiche_haut(i,j,c);
	        affiche_gauche(i,j,c);
	        affiche_droite(i,j,c);
	        affiche_all();
}
	
void affiche_joueur(GAME g)
{
	POINT P,Q;
	P.x = 470; P.y = 440;
	Q.x = 570;Q.y = 440;
	if(g.joueur == J1)
	{
		aff_pol("J1",50,P,rouge);
		aff_pol("J2",50,Q,noir);
	}
	if(g.joueur == J2)
	{
		aff_pol("J1",50,P,noir);
		aff_pol("J2",50,Q,bleu);
	}
	P.x = 460;P.y = 260;
	Q.x = 650;Q.y = 335;
	draw_fill_rectangle(P,Q,blanc);
	P.x = 475; P.y = 340;
	Q.x = 575;Q.y = 340;
	aff_int(g.M1,40,P,rouge);
	aff_int(g.M2,40,Q,bleu);

}

void affiche_retour(Liste l)
{
	POINT P,Q;
	P.x = 470;P.y = 200;
	Q.x = 620;Q.y = 280;
	draw_fill_rectangle(P,Q,blanc);
	if(l->suiv == NULL) draw_fill_rectangle(P,Q,gris); 
	else draw_rectangle(P,Q,noir);
	P.x =480;P.y = 270;
	aff_pol("Retour",40,P,noir);
}
void affiche_save()
{
	POINT P,Q;
	P.x = 470;P.y = 110;
	Q.x = 620;Q.y = 190;
	draw_fill_rectangle(P,Q,blanc);
	draw_rectangle(P,Q,noir);
	P.x =495;P.y = 175;
	aff_pol("Save",40,P,noir);
}

void affiche_load()
{
	POINT P,Q;
	P.x = 470;P.y = 10;
	Q.x = 620;Q.y = 100;
	draw_fill_rectangle(P,Q,blanc);
	draw_rectangle(P,Q,noir);
	P.x =495;P.y = 75;
	aff_pol("Load",40,P,noir);
}
void affichage(GAME g)
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{  
	        affiche_case(i,j,g.T[i][j]);
	        murs(i,j,g.T[i][j]);	        
	 	}
	}
 affiche_save();
 affiche_load();
 affiche_all();	
}

void afficher_victoire(int joueur)
{

	POINT P,Q;
	
	P.x = 460;P.y = 290;
	Q.x = 650;Q.y = 450;
	draw_fill_rectangle(P,Q,blanc);	
	P.x = 460; P.y = 400;  
	if(joueur == J1)
	{
		aff_pol("J1 WIN",50,P, rouge);
	}
	if(joueur == J2)
	{
		aff_pol("J2 WIN",50,P, bleu);
	}
	affiche_all();
}


