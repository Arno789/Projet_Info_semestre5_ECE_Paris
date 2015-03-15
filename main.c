#include "projet.h"


t_horloge horloge;
BITMAP* buffer=NULL;
BITMAP* image_acceuil=NULL;
BITMAP* horloge_image = NULL;
BITMAP* image_action_bo = NULL;
int acceleration=1;
int sortie=0;


void init_all ()
{
    initialiser_allegro();
    buffer = init_buffer(buffer);
    image_acceuil=chargerImage("blanc.bmp");
    horloge_image=chargerImage("clock.bmp");
    image_action_bo = chargerImage("action.bmp");

    init_temps ();
    init_plateau();
    init_action();
    init_construction ();
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
        affichage (image_acceuil);
        traitement_clique();
        temps(t1);
        rest (20);
    }
    return 0;
}
END_OF_MAIN ();
