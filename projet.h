#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>


#include "affichage.h"
#include "editeur.h"
#include "construction.h"

extern int acceleration;
extern t_horloge horloge;
extern int sortie;

void init_temps ();
void init_action();
void temps (clock_t t1);
void afficher_temps_allegro ();
void verification_sortie();


#endif // PROJET_H_INCLUDED
