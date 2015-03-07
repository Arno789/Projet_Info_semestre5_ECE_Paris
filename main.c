#include "projet.h"


t_horloge horloge;
BITMAP* buffer=NULL;
BITMAP* horloge_image = NULL;
int acceleration=1;


void init_temps ()
{
    horloge.an = 2015;
    horloge.mois = 5;
    horloge.jour = 1;
    horloge.heure = 12;
    horloge.minute = 0;
    horloge.seconde = 0;
    horloge.tic=0;
}

void temps (clock_t t1)
{
    clock_t t2;
    long clk_tck = CLOCKS_PER_SEC;
    t2 = clock();
    if (horloge.clock1 != (t2-t1)/clk_tck %60)
        horloge.tic=1;
    else horloge.tic=0;
    if (key[KEY_PLUS_PAD])
        acceleration++;
    else if (key[KEY_MINUS_PAD])
        acceleration--;
    horloge.clock1 = (t2-t1)/clk_tck%60;
    if (horloge.tic)
        horloge.seconde=horloge.seconde+acceleration;
    if (horloge.seconde>=60)
    {
        horloge.minute++;
        horloge.seconde=0;
    }
    if (horloge.minute>=60)
    {
        horloge.heure++;
        horloge.minute=0;
    }
    if (horloge.heure>=24)
    {
        horloge.heure = 0;
        horloge.jour++;
    }
    if (horloge.tic)
        afficher_temps_console ();
}


void afficher_temps_allegro ()
{
    int t,x,i;
    t=0;
    x=0;
    for (i=0; i<5; i++)
    {
        switch (i)
        {
        case 0:
            x=12*(horloge.minute/10);
            break;
        case 1 :
            x=12*(horloge.minute%10);
            break;
        case 2 :
            x = 120;
            break;
        case 3 :
            x=12*(horloge.seconde/10);
            break;
        case 4 :
            x=12*(horloge.seconde%10);
            break;
        }
        t=t+15;
        masked_blit (horloge_image, buffer, x, 0, SCREEN_W/2+t, SCREEN_H-100, 12, 55);

    }
    //printf("\n");

}



int main()
{
    BITMAP* image_acceuil;

    initialiser_allegro();
    buffer = init_buffer(buffer);
    image_acceuil=chargerImage("blanc.bmp");
    horloge_image=chargerImage("clock.bmp");

    init_temps ();

    clock_t t1;
    t1 = clock ();
    while (!key[KEY_ESC])
    {
        affichage (image_acceuil);
        temps(t1);
        rest (20);
    }
    return 0;
}
END_OF_MAIN ();
