#include "projet.h"

t_case* creer_route ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=0;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = 0;
    case_cree->bat->consommation_elec = 0;
    case_cree->bat->image_bat = chargerImage("route.bmp");
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'r';
    case_cree->bat->taille=1;
    return case_cree;
}

//void determiner_route ()
