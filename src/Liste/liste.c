#include "liste.h"

liste_entite creer_envahisseur(int pos_x, int pos_y, int sprite)
{ // Création d'un envahisseur en appliquant
  // à son pointeur la valeur NULL
    liste_entite* liste = malloc(sizeof(liste_entite));
    liste->position_x = pos_x;
    liste->position_y = pos_y;
    liste->sprite = sprite;
    liste->suivant = NULL;
    return *liste;
}

void ajout_tete_envahisseur(liste_entite* mob, liste_entite** ptr_liste_envahisseur)
{ // Permet d'ajouter à une liste d'envahisseur un nouvel
  // envahisseur en tête
    liste_entite* tmp = NULL;
    tmp = malloc(sizeof(liste_entite));
    tmp->position_x = mob->position_x;
    tmp->position_y = mob->position_y;
    tmp->sprite = mob->sprite;
    tmp->suivant = *ptr_liste_envahisseur;
    *ptr_liste_envahisseur = tmp;
}

void creer_liste_envahisseur(liste_entite** ptr_liste_envahisseur, int pos_x, int pos_y, int sprite)
{
    // Création d'une liste de  mobs.
    for (int i = 0; i < nb_mob_colonne; i++) {
        for (int j = 0; j < nb_colonne; j++) {
            liste_entite* mobx = NULL;
            mobx = malloc(sizeof(liste_entite));
            *mobx = creer_envahisseur(pos_x + j * esp_x, pos_y + i * esp_y, sprite);
            ajout_tete_envahisseur(mobx, ptr_liste_envahisseur);
        }
    }
}

liste_bouclier creer_bouclier(int pos_x, int pos_y, int sprite)
{ // Création d'un  bouclier avec son sprite et son nb de pv choisit dans const.h
    liste_bouclier* liste = malloc(sizeof(liste_bouclier));
    liste->position_x = pos_x;
    liste->position_y = pos_y;
    liste->sprite = sprite;
    liste->pv = nb_pv;
    liste->suivant = NULL;
    return *liste;
}

void ajout_tete_bouclier(struct liste_bouclier* liste_bouclier, struct liste_bouclier** ptr_liste_bouclier)
{ // Permet de faire un ajout en tete de bouclier dans une liste de bouclier
    struct liste_bouclier* tmpp = malloc(sizeof(struct liste_bouclier));
    tmpp->position_x = liste_bouclier->position_x;
    tmpp->position_y = liste_bouclier->position_y;
    tmpp->sprite = liste_bouclier->sprite;
    tmpp->pv = liste_bouclier->pv;
    tmpp->suivant = *ptr_liste_bouclier;
    *ptr_liste_bouclier = tmpp;
}

void creer_liste_bouclier(struct liste_bouclier** ptr_liste_bouclier, int sprite_bouclier)
{ // Permet de creer une liste de bouclier aux positions choisit dans const.h avec le nombre de boucliers
    int largeur_entre_bouclier = largeur_ecran / (nb_bouclier + 1);
    int largeur_bouclier[2];
    tailleLutin(sprite_bouclier, &largeur_bouclier[0], &largeur_bouclier[1]);
    largeur_bouclier[0] = largeur_bouclier[0] / 2;
    for (int i = 1; i <= nb_bouclier; i++) {
        struct liste_bouclier* bouclier_i = malloc(sizeof(liste_bouclier));
        *bouclier_i = creer_bouclier(largeur_entre_bouclier * i - largeur_bouclier[0], position_y_bouclier, sprite_bouclier);
        ajout_tete_bouclier(bouclier_i, ptr_liste_bouclier);
    }
}

defenseur init_defenseur(int sprite_canon)
{
    int largeur_canon[2];
    tailleLutin(sprite_canon, &largeur_canon[0], &largeur_canon[1]);
    defenseur canon;
    canon.position_x = (largeur_ecran / 2) - (largeur_canon[0] / 2);
    canon.position_y = position_y_canon;
    canon.sprite = sprite_canon;
    canon.pv = pv_canon_debut;
    return canon;
}

void imprime_ligne_mob(liste_entite* liste_envahisseur)
{ // Permet d'imprimer les positions X et
  // Y des envahisseurs dans le terminal
    printf("\t\t\t Début \n");
    while (liste_envahisseur != NULL) {
        printf("x=%d  y=%d --> ", liste_envahisseur->position_x, liste_envahisseur->position_y);
        liste_envahisseur = liste_envahisseur->suivant;
    }
    printf("NULL\n");
    printf("\t\t\t Fin \n");
}

void affiche(liste_entite* liste_envahisseur, liste_bouclier* liste_bouclier, defenseur canon, missile* missile /* , missile bo, ovni o*/)
{ // Permet d'afficher les envahisseurs, les missiles, les missiles, lesboucliers et l'ovni.
    liste_entite* tmp_envahisseur = NULL;
    tmp_envahisseur = liste_envahisseur;
    struct liste_bouclier* tmp_bouclier = NULL;
    tmp_bouclier = liste_bouclier;
    if (tmp_envahisseur != NULL) {
        while (tmp_envahisseur != NULL) {
            afficherLutin(tmp_envahisseur->sprite, tmp_envahisseur->position_x, tmp_envahisseur->position_y);
            tmp_envahisseur = tmp_envahisseur->suivant;
        }
    }
    if (tmp_bouclier != NULL) {
        while (tmp_bouclier != NULL) {
            afficherLutin(tmp_bouclier->sprite, tmp_bouclier->position_x, tmp_bouclier->position_y);
            tmp_bouclier = tmp_bouclier->suivant;
        }
    }
    while (tmp_envahisseur != NULL) {
        // Libération mémoire tmp_envahisseur
        liste_entite* tmp = tmp_envahisseur;
        tmp_envahisseur = tmp_envahisseur->suivant;
        free(tmp);
    }
    while (tmp_bouclier != NULL) {
        // Libération mémoire tmp_bouclier
        struct liste_bouclier* tmp = tmp_bouclier;
        tmp_bouclier = tmp_bouclier->suivant;
        free(tmp);
    }
    afficherLutin(canon.sprite, canon.position_x, canon.position_y);
    afficherLutin(missile->sprite, missile->position_x, missile->position_y);
}

void modif(liste_entite** ptr_liste_envahisseur, int direction_x, int direction_y, int sprite)
{
    // Permet de modifier les coordonnées des envahisseurs d'une liste
    // d'envahisseurs
    liste_entite* tmp = NULL;
    tmp = *ptr_liste_envahisseur;
    int increment = 0;
    if (tmp != NULL) {
        increment++;
        tmp->sprite = sprite;
        tmp->position_x = tmp->position_x + direction_x;
        tmp->position_y = tmp->position_y + direction_y;
        modif(&tmp->suivant, direction_x, direction_y, sprite);
    }
    *ptr_liste_envahisseur = tmp;
}

int bord_gauche(liste_entite* liste_envahisseur)
{
    // Renvoie le bord gauche de la liste des envahisseurs
    liste_entite* tmp = NULL;
    tmp = liste_envahisseur;
    int min_x = tmp->position_x;
    while (tmp != NULL) {
        if (tmp->position_x < min_x) {
            min_x = tmp->position_x;
        }
        tmp = tmp->suivant;
    }
    while (tmp != NULL) {
        liste_entite* tmpp = tmp;
        tmp = tmp->suivant;
        free(tmpp);
    }
    return min_x;
}

int bord_droite(liste_entite* liste_envahisseur)
{
    // Renvoie le bord droit de la liste des envahisseurs
    liste_entite* tmp = NULL;
    tmp = liste_envahisseur;
    int max_x = tmp->position_x;
    while (tmp != NULL) {
        if (tmp->position_x > max_x) {
            max_x = tmp->position_x;
        }
        tmp = tmp->suivant;
    }
    while (tmp != NULL) {
        liste_entite* tmpp = tmp;
        tmp = tmp->suivant;
        free(tmpp);
    }
    return max_x;
}


int bas(liste_entite* liste_envahisseur)
{
    // Renvoie le bord droit de la liste des envahisseurs
    liste_entite* tmp = NULL;
    tmp = liste_envahisseur;
    int max_y = tmp->position_y;
    while (tmp != NULL) {
        if (tmp->position_y > max_y) {
            max_y = tmp->position_y;
        }
        tmp = tmp->suivant;
    }
    while (tmp != NULL) {
        liste_entite* tmpp = tmp;
        tmp = tmp->suivant;
        free(tmpp);
    }
    return max_y;
}


int test_collision(int pos_x_1, int largeur_x_1, int pos_y_1, int largeur_y_1, int pos_x_2, int largeur_x_2, int pos_y_2, int largeur_y_2)
{ // renvoie 1 si collision entre 2 rectangles (sprites) avec les position (x;y) et les largeurs longueurs des deux rectangles sinon renvoie 0
    return ((((pos_x_1 <= pos_x_2 + largeur_x_2 && pos_x_1 >= pos_x_2) || (pos_x_2 <= pos_x_1 + largeur_x_1 && pos_x_2 + largeur_x_2 >= pos_x_1))) && (((pos_y_1 <= pos_y_2 + largeur_y_2 && pos_y_1 >= pos_y_2) || (pos_y_2 <= pos_y_1 + largeur_y_1 && pos_y_2 + largeur_y_2 >= pos_y_1))));
}

void collision_envahisseur(missile* missile, liste_entite** ptr_liste_envahisseur, defenseur* canon, int* jeu)
{
    // Permet de supprimer un envahisseur s'il est touché par une missile
    // Si il y a une collision entre un envahisseur et le canon le jeu se stop
    int* ptr_jeu = jeu;
    liste_entite* tmp = NULL;
    tmp = *ptr_liste_envahisseur;
    liste_entite* prev = NULL;
    int largeur_envahisseur[2];
    int largeur_missile[2];
    int largeur_canon[2];
    int sprite_canon = canon->sprite;
    int sprite_alien = tmp->sprite;
    int sprite_missile = missile->sprite;
    tailleLutin(sprite_canon, &largeur_canon[0], &largeur_canon[1]);
    tailleLutin(sprite_alien, &largeur_envahisseur[0], &largeur_envahisseur[1]);
    tailleLutin(sprite_missile, &largeur_missile[0], &largeur_missile[1]);
    if (bas(*ptr_liste_envahisseur) > hauteur_ecran-largeur_envahisseur[1]){
        printf("haut :%d\n",hauteur_ecran);
        printf("bas :%d\n",bas(*ptr_liste_envahisseur));
        *ptr_jeu = 0;
        printf("GAME OVER\n");
    }
    while (tmp != NULL) {
        int position_x_envahisseur = tmp->position_x;
        int position_y_envahisseur = tmp->position_y;
        int position_x_missile = missile->position_x;
        int position_y_missile = missile->position_y;
        if (test_collision(position_x_envahisseur, largeur_envahisseur[0], position_y_envahisseur, largeur_envahisseur[1], canon->position_x, largeur_canon[0], canon->position_y, largeur_canon[1])) {
            *ptr_jeu = 0;
            printf("GAME OVER\n");
            return;
        } else if (test_collision(position_x_envahisseur, largeur_envahisseur[0], position_y_envahisseur, largeur_envahisseur[1], position_x_missile, largeur_missile[0], position_y_missile, largeur_missile[1]) && !(position_x_missile == repos_x && position_y_missile == repos_y) ) { // Si une missile touche un alien
            if (prev == NULL) {
                *ptr_liste_envahisseur = tmp->suivant;
            } else {
                prev->suivant = tmp->suivant;
            }
            missile->position_x = repos_x;
            missile->position_y = repos_y; // Missile affiché en bas à gauche de l'écran pour signaler qu'un autre missile est prêt à être tiré
        }
        prev = tmp;
        tmp = tmp->suivant;
    }
    while (tmp != NULL) {
        liste_entite* tmpp = tmp;
        tmp = tmp->suivant;
        free(tmpp);
    }
}

void deplacer_liste_mob(liste_entite** ptr_liste_envahisseur, int sprite_1, int vitesse, int* etat)
{ // Permet de faire bouger la liste de mob, renvoie l'état de la liste pour la prochaine itération:
    // Cette fonction doit aller dans une boucle qui s'arrete quand l'utilisateur aura decidé.
    // Exemple : etat = deplacer_liste_mob(&liste_mob, monstre1, 8, etat);.
    int largeur_envahisseur[2];
    tailleLutin(sprite_1, &largeur_envahisseur[0], &largeur_envahisseur[1]);
    if (*etat == -1) { // Initialisation du mouvement
        modif(ptr_liste_envahisseur, 1 * vitesse, 0, sprite_1);
        *etat = 1;
    } else if (((bord_droite(*ptr_liste_envahisseur) + largeur_envahisseur[0]) >= largeur_ecran) && *etat == 1) { // Saut quand la liste est arrivée tout à droite
        *etat = 0;
        modif(ptr_liste_envahisseur, 0, saut, sprite_1);
    } else if (bord_gauche(*ptr_liste_envahisseur) == 0 && *etat == 0) { // Saut quand la liste est arrivée tout à gauche
        *etat = 1;
        modif(ptr_liste_envahisseur, 0, saut, sprite_1);
    } else if (*etat == 1) { // Aller vers la droite
        modif(ptr_liste_envahisseur, 1 * vitesse, 0, sprite_1);
    } else if (*etat == 0) { // Aller vers la gauche
        modif(ptr_liste_envahisseur, -1 * vitesse, 0, sprite_1);
    }
}

void controle_canon(evenement evt, char touche, defenseur* canon, missile* missile)
{ // Permet de controler le canon avec les touches mises dans le fichier const.h
    // Cette fonction ne tire qu'un missile à la fois
    int largeur_canon[2];
    int largeur_missile[2];
    tailleLutin(canon->sprite, &largeur_canon[0], &largeur_canon[1]);
    tailleLutin(missile->sprite, &largeur_missile[0], &largeur_missile[1]);
    if (evt == toucheBas) {
        if (touche == depl_gauche && canon->position_x > 0) {
            canon->position_x -= pas_canon;
        } else if (touche == depl_droite && canon->position_x < largeur_ecran - largeur_canon[0]) {
            canon->position_x += pas_canon;
        } else if (touche == tir_missile && missile->position_x == repos_x && missile->position_y == repos_y) {
            missile->position_x = canon->position_x - largeur_missile[0] / 2 + largeur_canon[0] / 2 - 1;
            missile->position_y = canon->position_y + largeur_canon[1] - largeur_missile[1];
        }
    }
}

missile* init_missile(int sprite_missile, int pos_x, int pos_y)
{
    // Permet d'Initialiser un missile
    missile* missile = malloc(sizeof(struct missile));
    missile->position_x = pos_x;
    missile->position_y = pos_y;
    missile->sprite = sprite_missile;
    return missile;
}

void deplacer_missile(missile* missile)
{
    if (missile->position_y < 0) {
        missile->position_y = repos_y;
        missile->position_x = repos_x;
    } else if (missile->position_y == repos_y && missile->position_x == repos_x) {
    } else {
        missile->position_y -= deplacement_missile;
    }
}

void collision_bouclier(missile* missile, liste_bouclier** ptr_liste_bouclier, liste_entite* liste_envahisseur)
{
    liste_bouclier* prev = NULL;
    liste_bouclier* tmpb = NULL;
    tmpb = *ptr_liste_bouclier;
    liste_entite* tmpe = liste_envahisseur;
    int largeur_envahisseur[2];
    int largeur_missile[2];
    int largeur_bouclier[2];
    int sprite_canon = tmpb->sprite;
    int sprite_alien = tmpe->sprite;
    int sprite_missile = missile->sprite;
    tailleLutin(sprite_canon, &largeur_bouclier[0], &largeur_bouclier[1]);
    tailleLutin(sprite_alien, &largeur_envahisseur[0], &largeur_envahisseur[1]);
    tailleLutin(sprite_missile, &largeur_missile[0], &largeur_missile[1]);
    while (tmpb != NULL) {
        // Parcours de la liste de boucliers
        tmpe = liste_envahisseur; // Réinitialisation de la liste d'envahisseurs à chaque tour de boucle de la liste de boucliers
        while (tmpe != NULL) {
            // Parcours de la liste d'envahisseurs
            if (test_collision(tmpe->position_x,largeur_envahisseur[0],tmpe->position_y,largeur_envahisseur[1],tmpb->position_x,largeur_bouclier[0],tmpb->position_y,largeur_bouclier[1])) {
                // Si un envahisseur touche un bouclier, le bouclier à ses pv à 0
                tmpb->pv = 0;
            }
            tmpe = tmpe->suivant;
        }
        if (test_collision(missile->position_x, largeur_missile[0], missile->position_y, largeur_missile[1],tmpb->position_x, largeur_bouclier[0], tmpb->position_y, largeur_bouclier[1])) {
            tmpb->pv--;
            missile->position_y = repos_y;
            missile->position_x = repos_x;
        }
        if (tmpb->pv == 0) {
            if (prev == NULL) {
                // Si l'élément à supprimer est en tête de la liste, on met à jour le pointeur de début de la liste
                *ptr_liste_bouclier = tmpb->suivant;
            } else {
                // Sinon, on met à jour le pointeur de l'élément précédent pour qu'il pointe vers l'élément suivant après celui qui doit être supprimé
                prev->suivant = tmpb->suivant;
            }
        }
        prev = tmpb; // Mettre à jour prev avec l'élément courant
        tmpb = tmpb->suivant;

 }
    while (tmpe != NULL) {
        liste_entite* tmpp = tmpe;
        tmpe = tmpe->suivant;
        free(tmpp);
    }
    while (tmpb != NULL) {
        liste_bouclier* tmpp_b = tmpb;
        tmpb = tmpb->suivant;
        free(tmpp_b);
    }
}

void missile_pret(missile* missile, int texte){
    if (missile->position_y == repos_y && missile->position_x == repos_x)
    {
        afficherLutin(texte,500,500);
    }
}
