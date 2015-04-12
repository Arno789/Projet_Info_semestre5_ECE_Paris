#include "projet.h"

void evenement(t_ville* ville, t_info_BFS* info)
{
    if (horloge.tic)
    {
        update_eau(ville, info);
        update_elec(ville, info);
        incrementation_age(ville)
    }
}


void incrementation_age (t_ville* ville)
{
    int i,j;
    for (i=0 ; i < LARGEUR_PLATEAU ; i++)
        for (j=0 ; j < HAUTEUR_PLATEAU ; j++)
            if (ville->plateau[i][j]->construction)
                ville->plateau[i][j]->age++;
}


void evolution (t_ville* ville)
{
    int i,j;
    for (i=0 ; i < LARGEUR_PLATEAU ; i++)
        for (j=0 ; j < HAUTEUR_PLATEAU ; j++)
            if (ville->plateau[i][j]->construction)
                if (ville->plateau[i][j]->age%15 == 14)
                    evolution_case (ville, i, j);
}

void evolution_case (t_ville* ville, int i, int j)
{

    if (ville->plateau[i][j]->appro_eau == ville->plateau[i][j]->bat->consommation_eau && ville->plateau[i][j]->appro_elec= ville->plateau[i][j]->bat->consommation_elec)
        ///Faire évoluer la case
        /// switch (ville->plateau[i][j]->bat->type)
        /// case 'm': ...

    if (ville->mode_de_jeu == 1)
    {

    }
    else if (ville->mode_de_jeu == 2)
    {

    }
}
