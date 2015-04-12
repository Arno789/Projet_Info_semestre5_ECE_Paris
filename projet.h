#ifndef PROJET_H_INCLUDED
#define PROJET_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <math.h>

#include "horloge.h"
#include "ville.h"
#include "route.h"
#include "construction.h"
#include "editeur.h"
#include "case.h"
#include "eau.h"
#include "elec.h"


#include "affichage.h"
#include "evenement.h"
#include "sauvegarder.h"
#include "charger.h"


extern int acceleration; ///Variable globale controlant la rapiditée du temps
extern t_horloge horloge; /// Déclaration de la structure globale horloge
extern int sortie; /// Déclaration de la variable globale qui provoque la sortie de la boucle de jeu si ==1

void init_image();


void verification_sortie(); ///SP qui check toutes les conditions pouvant vérifier l'intéruption de la boucle de jeu
void actualiser_coord ();

#endif // PROJET_H_INCLUDED
