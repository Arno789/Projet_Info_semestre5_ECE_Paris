#include "projet.h"

int test_constru=0;



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
    case_cree->bat->image_bat = im_maison_lv1;
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
    case_cree->bat->image_bat = im_commerce_lv1;
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
    case_cree->bat->image_bat = im_industrie_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'i';
    return case_cree;
}


void init_construction (t_construction* construction)
{
    construction->case_a_construire=NULL;
    construction->construction=0;
}


void placement (t_ville* ville, t_construction* construction)
{
    if (!ville->plateau [ville->coord_X][ville->coord_Y]->construction && mouse_click)
    {
        ville->plateau [ville->coord_X][ville->coord_Y]=construction->case_a_construire;
        construction->construction=0;
    }
}


void afficher_construction_en_cours (t_ville* ville, t_affichage* affichage_info, t_construction* construction)
{
    actualiser_coord (ville, affichage_info);
    if (construction->construction && construction->case_a_construire)
    {
        if (!ville->plateau [ville->coord_X][ville->coord_Y]->construction)
            if (construction->case_a_construire->bat->image_bat!=NULL)
                stretch_sprite(buffer, construction->case_a_construire->bat->image_bat, TAILLE_CASE*ville->coord_X*affichage_info->zoom, TAILLE_CASE*ville->coord_Y*affichage_info->zoom, TAILLE_CASE*affichage_info->zoom, TAILLE_CASE*affichage_info->zoom);
    }
}
