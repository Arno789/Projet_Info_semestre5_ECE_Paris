#include "projet.h"

t_horloge horloge;
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
    long clk_tck;

    if (acceleration)
        clk_tck = CLOCKS_PER_SEC/acceleration;

    if (key_press[KEY_PLUS_PAD] && acceleration<4)
    {
        acceleration++;
        printf ("acceleration : %d\n", acceleration);
    }
    else if (key_press[KEY_MINUS_PAD] && acceleration>0)
    {
        acceleration--;
        printf ("acceleration : %d\n", acceleration);
    }

    t2 = clock();

    if (acceleration && horloge.clock1 != (t2-t1)/clk_tck %60)
    {
        horloge.tic=1;
        horloge.seconde++;
    }
    else horloge.tic=0;

    if (acceleration)
        horloge.clock1 = (t2-t1)/clk_tck%60;

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
    /*if (horloge.tic)
        afficher_temps_console ();*/
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
        masked_blit (horloge_image, buffer, x, 0, 10+t, SCREEN_H-40, 12, 55);

    }
}


void afficher_temps_console ()
{
    printf("%d/%d/%d %d:%d:%d\n", horloge.jour, horloge.mois, horloge.an, horloge.heure, horloge.minute, horloge.seconde);
}
