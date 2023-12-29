#include "../Constante/const.h"
#include "../Graphique/libgraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct liste_entite {
    int position_x;
    int position_y;
    int sprite;
    struct liste_entite* suivant;
} liste_entite;

typedef struct missile {
    int position_x;
    int position_y;
    int sprite;
} missile;

typedef struct liste_bouclier {
    int position_x;
    int position_y;
    int sprite;
    int pv;
    struct liste_bouclier* suivant;
} liste_bouclier;

typedef struct defenseur {
    int position_x;
    int position_y;
    int sprite;
    int pv;
} defenseur;

liste_entite creer_envahisseur(int pos_x, int pos_y, int sprite);
void ajout_tete_envahisseur(liste_entite* mob, liste_entite** ptr_liste_envahisseur);
void creer_liste_envahisseur(liste_entite** ptr_liste_envahisseur, int pos_x, int pos_y, int sprite);

liste_bouclier creer_bouclier(int pos_x, int pos_y, int sprite);
void ajout_tete_bouclier(struct liste_bouclier* liste_bouclier, struct liste_bouclier** ptr_liste_bouclier);
void creer_liste_bouclier(struct liste_bouclier** ptr_liste_bouclier, int sprite_bouclier);

defenseur init_defenseur(int sprite_canon);

void imprime_ligne_mob(liste_entite* liste_envahisseur);
void affiche(liste_entite* liste_envahisseur, liste_bouclier* liste_bouclier, defenseur canon, missile* missile /*, missile bo, ovni o*/);

void modif(liste_entite** ptr_liste_envahisseur, int direction_x, int direction_y, int sprite);

int bord_gauche(liste_entite* liste_envahisseur);
int bord_droite(liste_entite* liste_envahisseur);
int bas(liste_entite* liste_envahisseur);

int test_collision(int pos_x_1, int largeur_x_1, int pos_y_1, int largeur_y_1, int pos_x_2, int largeur_x_2, int pos_y_2, int largeur_y_2);
void collision_envahisseur(missile* missile, liste_entite** ptr_liste_envahisseur, defenseur* canon, int* jeu);
void deplacer_liste_mob(liste_entite** ptr_liste_envahisseur, int sprite_1, int vitesse, int* etat);

void controle_canon(evenement evt, char touche, defenseur* canon, missile* missile);

missile* init_missile(int sprite_missile, int pos_x, int pos_y);
void deplacer_missile(missile* missile);

void collision_bouclier(missile* missile, liste_bouclier** ptr_liste_bouclier, liste_entite* liste_envahisseur);

void missile_pret(missile* missile, int texte);
