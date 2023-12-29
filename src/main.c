#include "Liste/liste.h"
int main()
{
    // Chargement des différents sprites utiles et texte pour le jeu .
    int monstre1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 1);
    int sprite_bouclier = chargerLutin("../Lutins/invader_bouclier.bmp", 1);
    int sprite_canon = chargerLutin("../Lutins/invader_canon.bmp", 1);
    int sprite_missile = chargerLutin("../Lutins/invader_missile.bmp", 1);
    choisirPolice("../Lutins/Discord.ttf", 10);
    // Initialisation du canon et du missile
    defenseur canon = init_defenseur(sprite_canon);
    evenement evt;
    char touche;
    missile* missile = init_missile(sprite_missile, repos_x, repos_y);

    // Initialisation des listes de boucliers et d'envahisseurs
    struct liste_entite* liste_envahisseur = NULL;
    struct liste_bouclier* liste_boucliers = NULL;
    int* etat = malloc(sizeof(int));
    *etat = -1; // Initialisation necessaire pour faire bouger la liste via la fonction deplacer_liste_mob.
    int* jeu = malloc(sizeof(int));
    *jeu = 1;
    creer_liste_bouclier(&liste_boucliers, sprite_bouclier);
    creer_liste_envahisseur(&liste_envahisseur, 0, 0, monstre1);

    // Création de la fenêtre de jeu
    creerSurface(largeur_ecran, hauteur_ecran, "SPACE INVADERS");

    // Boucle de jeux
    while (*jeu) {
        // Lecture des événements pour quitter ou non le jeux
        lireEvenement(&evt, &touche, NULL);
        if (evt == quitter) {
            printf("ABANDON\n");
            *jeu = 0;
        }

        // Déplacement des envahisseurs, du canon et du missile
        deplacer_liste_mob(&liste_envahisseur, monstre1, distance_deplacement_envahisseur, etat);
        controle_canon(evt, touche, &canon, missile);
        deplacer_missile(missile);

        // Test collision et supprission d'éléments
        collision_envahisseur(missile, &liste_envahisseur, &canon, jeu);
        if (liste_boucliers != NULL && liste_envahisseur != NULL) { // Si la liste de bouclier est vide, ne pas tester les colissions des boucliers.
            collision_bouclier(missile, &liste_boucliers, liste_envahisseur);
        }

        // Affichage des différentes structures à l'écran
        rectanglePlein(0, 0, largeur_ecran, hauteur_ecran, 1);
        affiche(liste_envahisseur, liste_boucliers, canon, missile);
        
        majSurface();
        // Delais de rafraichissement
        usleep(attente);
        // Affichage d'une message si le joueur gagne la partie
        if (liste_envahisseur == NULL) {
            *jeu = 0;
            printf("Well Done, you saved the World !\n");
        }
    }
    while (liste_envahisseur != NULL) {
        liste_entite* tmpp_b = liste_envahisseur;
        liste_envahisseur = liste_envahisseur->suivant;
        free(tmpp_b);
    }
    while (liste_boucliers != NULL) {
        liste_bouclier* tmpp_b = liste_boucliers;
        liste_boucliers = liste_boucliers->suivant;
        free(tmpp_b);
    }
    return 0;
}
