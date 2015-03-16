#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>

#include "horloge.h"
#include "affichage.h"
#include "ville.h"
#include "case.h"
#include "editeur.h"
#include "construction.h"
#include "route.h"
#include "sauvegarder.h"
#include "charger.h"


extern int acceleration; ///Variable globale controlant la rapiditée du temps
extern t_horloge horloge; /// Déclaration de la structure globale horloge
extern int sortie; /// Déclaration de la variable globale qui provoque la sortie de la boucle de jeu si ==1

void init_image();
void init_temps ();
void temps (clock_t t1);
void afficher_temps_allegro ();
void verification_sortie(); ///SP qui check toutes les conditions pouvant vérifier l'intéruption de la boucle de jeu
void actualiser_coord ();

#endif // PROJET_H_INCLUDED
