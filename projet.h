#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>


#include "affichage.h"
#include "editeur.h"

extern int acceleration;
extern t_horloge horloge;

void init_temps ();
void temps (clock_t t1);
void afficher_temps_allegro ();


#endif // PROJET_H_INCLUDED
