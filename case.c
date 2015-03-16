#include "projet.h"


t_case* init_case ()
{
    t_case* tcase;
    tcase = malloc(sizeof(t_case));
    tcase->bat = malloc(sizeof(t_bat));
    tcase->construction=0;
    tcase->densite=0;
    tcase->hapiness=0;
    tcase->bat->consommation_eau=0;
    tcase->bat->consommation_elec=0;
    tcase->bat->image_bat=NULL;
    tcase->bat->type='n';
    return tcase;
}
