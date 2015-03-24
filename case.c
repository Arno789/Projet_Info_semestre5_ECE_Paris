#include "projet.h"


t_case* init_case (t_case* tcase)
{
    tcase->bat = malloc(sizeof(t_bat));
    tcase->construction=0;
    tcase->densite=0;
    tcase->hapiness=0;
    tcase->bat->consommation_eau=0;
    tcase->bat->consommation_elec=0;
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
    //printf("%p  -  %p",tcase, tcase->bat);
    if (tcase->bat->image_bat)
    {
        stretch_sprite (buffer, tcase->bat->image_bat, x, y, TAILLE_CASE*affichage_info->zoom, TAILLE_CASE*affichage_info->zoom);
    }

}
