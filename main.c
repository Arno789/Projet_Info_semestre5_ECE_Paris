#include "projet.h"


int sortie=0;


void init_all (t_ville* ville, t_affichage* affichage_info, t_construction* construction)
{
    initialiser_allegro();
    buffer = init_buffer(buffer);
    terrain_jeu=chargerImage("terrain.bmp");
    horloge_image=chargerImage("clock.bmp");
    image_action_bo = chargerImage("construction_couleur.bmp");
    boconst = chargerImage("construction.bmp");
    init_buffer_image();

    init_image();
    init_temps ();
    init_affichage_info (affichage_info);
    init_ville(ville);
    init_construction (construction);
}

void actualiser_coord (t_ville* ville, t_affichage* affichage_info)
{
    ville->coord_X=(mouse_x + affichage_info->zoom * affichage_info->depX)/TAILLE_CASE/affichage_info->zoom; ///Déduit avec le théorème "de la grosse chatte de 00h18" ...
    ville->coord_Y=(mouse_y + affichage_info->zoom * affichage_info->depY)/TAILLE_CASE/affichage_info->zoom;

    if (ville->coord_X<0)
        ville->coord_X=0;
    if (ville->coord_Y<0)
        ville->coord_Y=0;

    if (ville->coord_Y>HAUTEUR_PLATEAU-1)
        ville->coord_Y=HAUTEUR_PLATEAU-1;
    if (ville->coord_X>LARGEUR_PLATEAU-1)
        ville->coord_X=LARGEUR_PLATEAU-1;
        printf("X: %d - Y: %d\tmouse_x: %d - mouse_y: %d  \tdepX: %d - depY: %d\n", ville->coord_X, ville->coord_Y, mouse_x, mouse_y, affichage_info->depX, affichage_info->depY);
        printf("zoom : %f\n", affichage_info->zoom);
}

void verification_sortie(t_construction* construction)
{
    if (key_press[KEY_ESC])
    {
        if (construction->construction)
        {
            construction->construction=0;
            free(construction->case_a_construire);
            construction->case_a_construire=NULL;
        }
        else if (!construction->construction)
            sortie=1;
    }
}

int main()
{
    t_ville* ville= malloc (sizeof (t_ville));
    t_affichage* affichage_info= malloc( sizeof (t_affichage));
    t_construction* construction=malloc(sizeof(t_construction));
    init_all(ville, affichage_info, construction);
    clock_t t1;
    t1 = clock ();

    while (!sortie)
    {
        rafraichir_clavier_souris();
        verification_sortie(construction);
        traitement_clique(ville, construction);
        temps(t1);
        affichage (ville, affichage_info, construction);
        rest (20);
    }
    return 0;
}
END_OF_MAIN ();
