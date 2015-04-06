#include "projet.h"


t_case* init_case (t_case* tcase)
{
    tcase->bat = malloc(sizeof(t_bat));
    tcase->construction=0;
    tcase->densite=0;
    tcase->hapiness=0;
    tcase->bat->consommation_eau=0;
    tcase->bat->consommation_elec=0;
    tcase->bat->taille=0;
    tcase->bat->image_bat=NULL;
    tcase->bat->type='n';
    return tcase;
}

/*
void afficher_case_matrice()
{
    int x1, y1, x2, y2;
    x1 = TAILLE_CASE*coord_X*zoom;
    y1 = TAILLE_CASE*coord_Y*zoom;
    x2 = (TAILLE_CASE*(coord_X+1))*zoom;
    y2 = (TAILLE_CASE*(coord_Y+1))*zoom;

    if (ville->plateau [coord_X] [coord_Y]->bat && ville->plateau [coord_X] [coord_Y]->bat->image_bat)
        stretch_sprite(buffer_terrain, ville->plateau [coord_X] [coord_Y]->bat->image_bat, TAILLE_CASE*coord_X*zoom, TAILLE_CASE*coord_Y*zoom, TAILLE_CASE*zoom, TAILLE_CASE*zoom);
    else if ((coord_X+coord_Y)%2)
        rectfill(buffer, x1, y1,x2, y2, makecol (200,200,200));
}
*/

void afficher_case_matrice(t_case* tcase, int x, int y, t_affichage* affichage_info)
{
    if (tcase->bat->image_bat)
    {
        //stretch_sprite (buffer, tcase->bat->image_bat, x, y, tcase->bat->taille*TAILLE_CASE*affichage_info->zoom, tcase->bat->taille*TAILLE_CASE*affichage_info->zoom);
        rotate_scaled_sprite(buffer, tcase->bat->image_bat, x, y, itofix (tcase->bat->rotation), ftofix (affichage_info->zoom));
        //draw_sprite (buffer, tcase->bat->image_bat, x, y);
    }
}

void afficher_case_grille_construction (t_ville* ville, int x, int y, t_affichage* affichage_info)
{
    int col;
    if (!ville->plan_construction[ville->coord_X][ville->coord_Y])
        col = makecol (150,20,30);
    else if (ville->plan_construction[ville->coord_X][ville->coord_Y]==1)
        col = makecol (0,200,30);
    else if (ville->plan_construction[ville->coord_X][ville->coord_Y]==2)
        col = makecol (0,30,200);

    if (ville->plateau[ville->coord_X][ville->coord_Y]->bat->type=='r')
        col = makecol (100,100,100);
    rectfill (buffer, x, y, TAILLE_CASE*affichage_info->zoom+x,TAILLE_CASE*affichage_info->zoom+y, col);
}
