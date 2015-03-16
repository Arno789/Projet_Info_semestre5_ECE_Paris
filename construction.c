#include "projet.h"

t_construction* construction;



t_case* creer_maison ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_MAISON_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_MAISON_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_MAISON_LV1;
    case_cree->bat->image_bat = chargerImage("maison_lv1.bmp");
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'm';
    return case_cree;
}

t_case* creer_commerce ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_COMMERCE_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_COMMERCE_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_COMMERCE_LV1;
    case_cree->bat->image_bat = chargerImage("commerce_lv1.bmp");
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'c';
    return case_cree;
}


t_case* creer_industrie ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_INDUSTRIE_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_INDUSTRIE_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_INDUSTRIE_LV1;
    case_cree->bat->image_bat = chargerImage("industrie_lv1.bmp");
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'i';
    return case_cree;
}


void init_construction ()
{
    construction = malloc(sizeof (t_construction));
    construction->case_a_construire=NULL;
    construction->construction=0;
}


void placement ()
{
    if (!ville->plateau [coord_X][coord_Y]->construction && mouse_click)
    {
        ville->plateau [coord_X][coord_Y]=construction->case_a_construire;
        construction->construction=0;
    }
}

