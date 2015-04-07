#include "projet.h"


void init_ville(t_ville* ville)
{
    ville->prec_X=0;
    ville->prec_Y=0;
    ville->flouz=FLOUZ_INITIAL;
    ville->population=0;
    ville->plateau = malloc(LARGEUR_PLATEAU*sizeof(t_case**));
    ville->gestion_eau = malloc(LARGEUR_PLATEAU*sizeof(int*));
    ville->gestion_elec = malloc(LARGEUR_PLATEAU*sizeof(int*));
    ville->plan_construction = malloc(LARGEUR_PLATEAU*sizeof(int*));
    for (ville->coord_X=0 ; ville->coord_X<LARGEUR_PLATEAU ; ville->coord_X++)
    {
        ville->plateau [ville->coord_X] = malloc(HAUTEUR_PLATEAU*sizeof(t_case*));
        ville->gestion_eau[ville->coord_X] = malloc(LARGEUR_PLATEAU*sizeof(int));
        ville->gestion_elec[ville->coord_X] = malloc(LARGEUR_PLATEAU*sizeof(int));
        ville->plan_construction[ville->coord_X] = malloc(LARGEUR_PLATEAU*sizeof(int));
        for (ville->coord_Y=0 ; ville->coord_Y<HAUTEUR_PLATEAU ; ville->coord_Y++)
        {
            ville->plateau[ville->coord_X][ville->coord_Y] = malloc(sizeof (t_case));
            ville->plateau[ville->coord_X][ville->coord_Y] = init_case(ville->plateau[ville->coord_X][ville->coord_Y]);
            ville->gestion_eau[ville->coord_X][ville->coord_Y] = 0;
            ville->gestion_elec[ville->coord_X][ville->coord_Y] = 0;
            ville->plan_construction[ville->coord_X][ville->coord_Y] = 1;
            ville->plateau[ville->coord_X][ville->coord_Y]->marqueur = 0;
        }
    }
}


void afficher_ville (t_ville* ville, t_affichage* affichage_info)
{
    int x, y;
    int origine_x, origine_y;
    int premiere_case_X, premiere_case_Y;


    ville->coord_X=affichage_info->depX/TAILLE_CASE;   ///On détermine quelle sera la première case a être dessinée
    ville->coord_Y=affichage_info->depY/TAILLE_CASE;   ///

    origine_x=-affichage_info->depX%TAILLE_CASE + affichage_info->zoom*(affichage_info->depX/TAILLE_CASE)*TAILLE_CASE; ///On détermine les coordonées de l'origines de la case a afficher
    origine_y=-affichage_info->depY%TAILLE_CASE + affichage_info->zoom*(affichage_info->depY/TAILLE_CASE)*TAILLE_CASE;

    x = ville->coord_X + SCREEN_W/(affichage_info->zoom*TAILLE_CASE);   ///On determine quelle sera la dernière case affichéé
    y = ville->coord_Y + SCREEN_H/(affichage_info->zoom*TAILLE_CASE);


    if (ville->coord_X > ville->coord_X-ville->coord_X/affichage_info->zoom)
        ville->coord_X = ville->coord_X-ville->coord_X/affichage_info->zoom;
    if (ville->coord_Y > ville->coord_Y-ville->coord_Y/affichage_info->zoom)
        ville->coord_Y = ville->coord_Y-ville->coord_Y/affichage_info->zoom;

    if (x<0)
        x=0;
    if (x>LARGEUR_PLATEAU)
        x=LARGEUR_PLATEAU;
    if (y>HAUTEUR_PLATEAU)
        y=HAUTEUR_PLATEAU;
    //printf("x: %d - %d   y: %d - %d  zoom: %f  -  depX : %d  -  depY : %d\n", ville->coord_X, x,ville->coord_Y, y, affichage_info->zoom, affichage_info->depX, affichage_info->depY);

    premiere_case_X = affichage_info->depX/TAILLE_CASE;
    premiere_case_Y = affichage_info->depY/TAILLE_CASE;

    if (premiere_case_X<0)
        premiere_case_X=0;
    if (premiere_case_Y<0)
        premiere_case_Y=0;

    for (ville->coord_X=premiere_case_X; ville->coord_X < x ; ville->coord_X++)
    {
        for (ville->coord_Y=premiere_case_Y; ville->coord_Y < y ; ville->coord_Y++)
        {

            origine_x = (TAILLE_CASE*ville->coord_X-affichage_info->depX)*affichage_info->zoom;
            origine_y = (TAILLE_CASE*ville->coord_Y-affichage_info->depY)*affichage_info->zoom;

            //printf ("\n%d  -  %d\n%d  -  %d\n\n", origine_x, origine_y, ville->coord_X, ville->coord_Y);
            //printf("x: %d  -  y: %d  -  zoom: %f\n", x, y, affichage_info->zoom);
            if (key[KEY_C])
                afficher_case_grille_construction (ville, origine_x, origine_y, affichage_info);
            else afficher_case_matrice(ville->plateau[ville->coord_X][ville->coord_Y], origine_x, origine_y, affichage_info);
        }
    }
}

