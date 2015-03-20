#ifndef HORLOGE_H_INCLUDED
#define HORLOGE_H_INCLUDED


typedef struct horloge
{
    int seconde;
    int minute;
    int heure;
    int jour;
    int mois;
    int an;
    int tic;    ///Booléen, vaut 1 à chaque changement de seconde (ou plus vite en fct° de 'acceleration')
    long int clock1;   ///Je sais plus
} t_horloge;

void init_temps ();
void temps (clock_t t1);

void afficher_temps_allegro ();
void afficher_temps_console ();                 ///Explicite ?

#endif // HORLOGE_H_INCLUDED
