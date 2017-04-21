#include "affichage.h"
#include "graphics.h"
#include "enregistrer.h"
#include <stdio.h>
#include <stdlib.h>
//////////////
/////JOUER/////
//////////////
GAME initialisation()
{
	int i,j;
	GAME g;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			g.T[i][j].val = VIDE;
			
			if(j==0) g.T[i][j].Mbas = 1;
			else g.T[i][j].Mbas = 0;
			
			if(i==8) g.T[i][j].Mdroite = 1;
			else g.T[i][j].Mdroite = 0;
			
			if(j==8) g.T[i][j].Mhaut = 1;
			else g.T[i][j].Mhaut = 0;
			
			if(i==0) g.T[i][j].Mgauche = 1;
			else g.T[i][j].Mgauche = 0;
		}
	}
	g.T[4][0].val = J1;
	g.Pos[0][0] = 4; g.Pos[0][1] = 0;
	g.T[4][8].val = J2;
	g.Pos[1][0] = 4; g.Pos[1][1] = 8;
	g.M1 = 10;
	g.M2 = 10;
	g.joueur = J1;
	return g;	
}

int changement(GAME tmp,GAME g)
{
	int c = 0;
	if(tmp.Pos[0][0] != g.Pos[0][0]) c = 1;
	if(tmp.Pos[0][1] != g.Pos[0][1]) c = 1;
	if(tmp.Pos[1][0] != g.Pos[1][0]) c = 1;
	if(tmp.Pos[1][1] != g.Pos[1][1]) c = 1;
	if(tmp.M1 != g.M1) c = 1;
	if(tmp.M2 != g.M2) c = 1;
	return(c);
}

GAME saut(GAME g,int i,int j,int joueur)
{
	if(g.T[i][j].Mbas== 0 && g.T[i][j-1].val != joueur) 
	{
		g.T[i][j-1].val = ACCES;
	}
	if(g.T[i][j].Mhaut== 0 && g.T[i][j+1].val != joueur) 
	{
		g.T[i][j+1].val = ACCES;
    }
	if(g.T[i][j].Mgauche== 0 && g.T[i-1][j].val != joueur)
	{
		g.T[i-1][j].val = ACCES;
	}
	if(g.T[i][j].Mdroite== 0 && g.T[i+1][j].val != joueur)  
	{	
		 g.T[i+1][j].val = ACCES;
	}
	return g;
}

GAME Deplacer_pion(int i,int j,GAME g,int joueur)
{
	int x,y;
	POINT P;
	if(g.T[i][j].Mbas== 0 ) 
	{
		if(g.T[i][j-1].val== -joueur)
		{
			g = saut(g,i,j-1,joueur);
		}
		else g.T[i][j-1].val = ACCES;
	}
	if(g.T[i][j].Mhaut== 0 ) 
	{
		if(g.T[i][j+1].val == -joueur)
	    {
			g = saut(g,i,j+1,joueur);
		}
		else g.T[i][j+1].val = ACCES;
    }
	if(g.T[i][j].Mgauche== 0 )
	{
		if(g.T[i-1][j].val == -joueur)
	    {
			g = saut(g,i-1,j,joueur);
		}
		else g.T[i-1][j].val = ACCES;
	}
	if(g.T[i][j].Mdroite== 0 )  
	{	
		if(g.T[i+1][j].val == -joueur)
	    {
			g = saut(g,i+1,j,joueur);
		}
		else g.T[i+1][j].val = ACCES;
	}
	affichage(g);
	P = wait_clic();
	x = P.x/50;
	y = P.y/50;
	if(g.T[x][y].val == ACCES)
	{
	    g.T[x][y].val = joueur;
		if(joueur == J1)
		{
			g.Pos[0][0]= x; g.Pos[0][1] =y;
		}
		if(joueur == J2)
		{
			g.Pos[1][0]= x; g.Pos[1][1] =y;
		}
	    g.T[i][j].val = VIDE;
	}
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(g.T[i][j].val == ACCES) g.T[i][j].val = VIDE;
		}
	}
	return (g);
}

int fake_victory(GAME g,int joueur)
{
	int i;
	for(i=0;i<9;i++)
	{
		if(joueur == J1)
		{
			if(g.T[i][8].val == 7)
			{
				return 1;
			}
		}
		if(joueur == J2)
		{
			if(g.T[i][0].val == 7)
			{
				return 1;
			}
		}
	}
	return 0;
}

GAME Path_finding(GAME g,int i, int j, int joueur)
{
	g.T[i][j].val = 7;
	if(j-1 >=0)
	{
		if(g.T[i][j].Mbas == 0 && g.T[i][j-1].val!=7) 
		{
			//.T[i][j-1].val=7;
			g = Path_finding(g,i,j-1,joueur);
		}
	}
	if(j+1<9)
	{
		if(g.T[i][j].Mhaut == 0 && g.T[i][j+1].val!=7) 
		{
			//g.T[i][j+1].val=7;
			g = Path_finding(g,i,j+1,joueur);
		}
	}
	if(i-1 >=0)
	{
		if(g.T[i][j].Mgauche == 0 && g.T[i-1][j].val!=7)
		{
			//g.T[i-1][j].val=7;
			g =  Path_finding(g,i-1,j,joueur);
		}
	}
	if(i+1 < 9)
	{
		if(g.T[i][j].Mdroite == 0 && g.T[i+1][j].val!=7)   
		{	
			//g.T[i+1][j].val=7;
			g = Path_finding(g,i+1,j,joueur);
		}
	}
	return(g);
}

int bloquer(GAME g)
{
	int yolo;
	yolo = fake_victory(Path_finding(g,g.Pos[0][0],g.Pos[0][1],J1),J1);
	yolo = yolo + fake_victory(Path_finding(g,g.Pos[1][0],g.Pos[1][1],J2),J2);
	if(yolo==2) return(1);
	else return(0);
}

int Est_mur_vide(int x,int y,CASES c)
{
	if(x>5 && x<45 && y>5 && y<45) 	return(2);
	if(x>5 && x<45 && y<5) return(c.Mbas);
	if(x<5 && y>5 && y<45) return(c.Mgauche);
	if(x>45 && y<45 && y>5) return(c.Mdroite);
	if(x<45 && x>5 && y>45) return(c.Mhaut);
	return(1);
}

int reste_mur(int joueur,GAME g)
{
	if(joueur == J1)
	{
		if(g.M1 > 0) 
		{
			return(1);
		}
	}
	if(joueur == J2)
	{
		if(g.M2 > 0) 
		{
			return(1);
		}
	}
	return(0);
	//return(g);
}

GAME simulation(GAME g,int i,int j,int x,int y,int joueur)
{
	if(x>5 && x<45 && y<5 && i+1 < 9) 
	{
		if(Est_mur_vide(x,y,g.T[i+1][j])==0)
		{
			if(Est_mur_vide(48,10,g.T[i][j])==0 || Est_mur_vide(48,10,g.T[i][j-1])==0)
			
			{
				g.T[i][j].Mbas = 1; 
				g.T[i+1][j].Mbas = 1;
				g.T[i][j-1].Mhaut = 1; 
			   	g.T[i+1][j-1].Mhaut = 1;
				
			}
		}
	}
	if(x<5 && y>5 && y<45 && j+1 < 9) 
	{
		if(Est_mur_vide(x,y,g.T[i][j+1])==0)
		{
			if(Est_mur_vide(10,48,g.T[i][j])==0 || Est_mur_vide(10,48,g.T[i-1][j])==0)
			{	
				g.T[i][j].Mgauche = 1; 
				g.T[i][j+1].Mgauche = 1;
				g.T[i-1][j].Mdroite = 1; 
				g.T[i-1][j+1].Mdroite = 1;
			}
		}
	}
	if(x>45 && y<45 && y>5 && j+1 < 9)
	{
		if(Est_mur_vide(x,y,g.T[i][j+1])==0 )
		{
			if(Est_mur_vide(10,48,g.T[i][j])==0 || Est_mur_vide(10,48,g.T[i+1][j])==0)
			
			{
				g.T[i][j].Mdroite = 1; 
				g.T[i][j+1].Mdroite = 1;
				g.T[i+1][j].Mgauche = 1; 
				g.T[i+1][j+1].Mgauche = 1;
			}
		}
	} 
	if(x<45 && x>5 && y>45 && i+1 < 9) 
	{
		if(Est_mur_vide(x,y,g.T[i+1][j])==0)
		{
			if(Est_mur_vide(48,10,g.T[i][j])==0 || Est_mur_vide(48,10,g.T[i][j+1])==0)
			{
				g.T[i][j].Mhaut = 1; 
				g.T[i+1][j].Mhaut = 1;
				g.T[i][j+1].Mbas = 1; 
				g.T[i+1][j+1].Mbas = 1;
			}
		}
	}
	return(g);
}

GAME pose_mur(GAME g,int i,int j,int x,int y,int joueur)
{
	GAME tmp;
	tmp = simulation(g,i,j,x,y,joueur);
	if(x>5 && x<45 && y<5 && i+1 < 9) 
	{
		if(Est_mur_vide(x,y,g.T[i+1][j])==0)
		{
			if((Est_mur_vide(48,10,g.T[i][j])==0 || Est_mur_vide(48,10,g.T[i][j-1])==0) 
			&&  bloquer(tmp))
			
			{
				if(reste_mur(joueur,g)== 1)
				{
					g.T[i][j].Mbas = 1; 
					g.T[i+1][j].Mbas = 1;
					g.T[i][j-1].Mhaut = 1; 
					g.T[i+1][j-1].Mhaut = 1;
					if(joueur == J1) (g.M1)--;
					if(joueur == J2) (g.M2)--;
				}
			}
		}
	}
	if(x<5 && y>5 && y<45 && j+1 < 9) 
	{
		if(Est_mur_vide(x,y,g.T[i][j+1])==0)
		{
			if((Est_mur_vide(10,48,g.T[i][j])==0 || Est_mur_vide(10,48,g.T[i-1][j])==0)
			&& bloquer(tmp))
			{
				if(reste_mur(joueur,g)== 1)
				{
					g.T[i][j].Mgauche = 1; 
					g.T[i][j+1].Mgauche = 1;
					g.T[i-1][j].Mdroite = 1; 
					g.T[i-1][j+1].Mdroite = 1;
					if(joueur == J1) (g.M1)--;
					if(joueur == J2) (g.M2)--;
				}
			}
		}
	}
	if(x>45 && y<45 && y>5 && j+1 < 9)
	{
		if(Est_mur_vide(x,y,g.T[i][j+1])==0 )
		{
			if((Est_mur_vide(10,48,g.T[i][j])==0 || Est_mur_vide(10,48,g.T[i+1][j])==0)
			&&  bloquer(tmp))
			{
				if(reste_mur(joueur,g)== 1)
				{
					g.T[i][j].Mdroite = 1; 
					g.T[i][j+1].Mdroite = 1;
					g.T[i+1][j].Mgauche = 1; 
					g.T[i+1][j+1].Mgauche = 1;
					if(joueur == J1) (g.M1)--;
					if(joueur == J2) (g.M2)--;
				}
			}
		}
	} 
	if(x<45 && x>5 && y>45 && i+1<9) 
	{
		if(Est_mur_vide(x,y,g.T[i+1][j])==0)
		{
			if((Est_mur_vide(48,10,g.T[i][j])==0 || Est_mur_vide(48,10,g.T[i][j+1])==0)
			&&  bloquer(tmp))
			{
			    if(reste_mur(joueur,g)== 1)
			    {
					g.T[i][j].Mhaut = 1; 
					g.T[i+1][j].Mhaut = 1;
					g.T[i][j+1].Mbas = 1; 
					g.T[i+1][j+1].Mbas = 1;
					if(joueur == J1) (g.M1)--;
					if(joueur == J2) (g.M2)--;
				}
			}
		}
	}
	return(g);
}

Liste jouer(GAME g,int joueur,Liste l)
{
	int i,j,back;
	POINT P;
	P = wait_clic();
	back = 0;
	i = P.x/50;
	j = P.y/50;
	if(P.x >0 && P.x <450 && P.y > 0 && P.y <450)
	{
		if(g.T[i][j].val == g.joueur && Est_mur_vide((P.x)%50,(P.y)%50,g.T[i][j])== 2 )
		{ 
			g = Deplacer_pion(i,j,g,joueur);
		}
		else if(Est_mur_vide((P.x)%50,(P.y)%50,g.T[i][j]) == 0) 
		g = pose_mur(g,i,j,(P.x)%50,(P.y)%50,joueur);
    }
	else if(P.x > 470 && P.x< 620 && P.y > 200 && P.y < 280 && (l->suiv) != NULL)
	{
		return(SuppDebut(l));
		//g = l->tour;
    }
    else if(P.x > 470 && P.x< 620 && P.y > 110 && P.y < 190)
    {
		Save(g);
	}
    else if(P.x > 470 && P.x< 620 && P.y > 10 && P.y < 100)
    {
		g = Load();
		back = 1;
	}
    if(changement((l->tour),g)==1) 
    {
		if(back ==0) g.joueur = -(g.joueur);
		l = AjoutDebut(l,g);
	}
	return(l);
}

void Victoire(Liste l,GAME g)
{
	affiche_all();
	if(g.Pos[0][1] == 8)
	{
		printf("Le joueur 1 a gagné");
		vider_Liste(l);
		afficher_victoire(J1);
		wait_escape(0);
	}
	if(g.Pos[1][1] == 0)
	{
		printf("Le joueur 2 a gagné");
		vider_Liste(l);
		afficher_victoire(J2);
		wait_escape(0);
	}
}
