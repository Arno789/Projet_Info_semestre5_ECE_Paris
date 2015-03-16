#include "projet.h"


int sortie=0;


void init_all ()
{
    initialiser_allegro();
    buffer = init_buffer(buffer);
    image_acceuil=chargerImage("blanc.bmp");
    horloge_image=chargerImage("clock.bmp");
    image_action_bo = chargerImage("construction_couleur.bmp");
    boconst = chargerImage("construction.bmp");
    init_buffer_image();

    init_image();
    init_temps ();
    init_ville();
    init_construction ();
}

void actualiser_coord ()
{
    coord_X=(mouse_x+depX)/(zoom*TAILLE_CASE);
    coord_Y=(mouse_y+depY)/(zoom*TAILLE_CASE);
    if (coord_Y>34)
        coord_Y=34;
    if (coord_X>44)
        coord_X=44;
}

void verification_sortie()
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

    init_all();
    clock_t t1;
    t1 = clock ();

    while (!sortie)
    {
        rafraichir_clavier_souris();
        verification_sortie();
        traitement_clique();
        temps(t1);
        affichage (image_acceuil);
        rest (20);
    }
    return 0;
}
END_OF_MAIN ();
