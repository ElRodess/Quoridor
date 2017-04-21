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
int Pos[2][2];//Pos[0][] J1 & Pos[1][] J2
int M1; //Murs du joueur 1
int M2; //Murs du joueur 2
int joueur; //Tour de qui ?
};

struct element{
  struct game tour;
  struct element* suiv;
};

typedef struct element Element;
typedef Element* Liste;

typedef struct cases CASES;
typedef struct game GAME;

#define J1 1 
#define J2 -1 
#define VIDE 0
#define ACCES 5

void affiche_bas(int i,int j,CASES c);
void affiche_haut(int i,int j,CASES c);
void affiche_gauche(int i,int j,CASES c);
void affiche_droite(int i,int j,CASES c);
void affiche_case(int i,int j,CASES c);
void murs(int i,int j,CASES c);
void affiche_joueur(GAME g);
void affichage(GAME g);
void affiche_retour(Liste l);
void afficher_victoire(int joueur);
void affiche_save();
void affiche_load();
