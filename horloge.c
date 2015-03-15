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

