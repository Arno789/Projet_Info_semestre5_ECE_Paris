#include "projet.h"

t_case* plateau [LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
int coord_X, coord_Y;

void init_plateau ()
{
    for (coord_X=0; coord_X<LARGEUR_PLATEAU ; coord_X++)
    {
        for (coord_Y=0; coord_Y<HAUTEUR_PLATEAU ; coord_Y++)
        {
            plateau [coord_X][coord_Y] = malloc(sizeof(t_case*));
            plateau [coord_X][coord_Y]->bat = malloc(sizeof(t_bat*));
            plateau [coord_X][coord_Y]->construction=0;
            plateau [coord_X][coord_Y]->densite=0;
            plateau [coord_X][coord_Y]->hapiness=0;
            plateau [coord_X][coord_Y]->bat->consommation_eau=0;
            plateau [coord_X][coord_Y]->bat->consommation_elec=0;
            plateau [coord_X][coord_Y]->bat->image_bat=NULL;
        }
    }
}

void placer_maison ()
{
    plateau [coord_X][coord_Y]->construction=1;
    plateau [coord_X][coord_Y]->densite=DENS_MAISON_CTR;
    plateau [coord_X][coord_Y]->hapiness=0;
    plateau [coord_X][coord_Y]->bat->consommation_eau = CSMA_EAU_MAISON_LV1;
    plateau [coord_X][coord_Y]->bat->consommation_elec = CSMA_ELEC_MAISON_LV1;
    plateau [coord_X][coord_Y]->bat->image_bat = chargerImage("maison_lv1.bmp");
    plateau [coord_X][coord_Y]->bat->type = 'i';
}

void placer_commerce ()
{
    plateau [coord_X][coord_Y]->construction=1;
    plateau [coord_X][coord_Y]->densite=DENS_COMMERCE_CTR;
    plateau [coord_X][coord_Y]->hapiness=0;
    plateau [coord_X][coord_Y]->bat->consommation_eau = CSMA_EAU_COMMERCE_LV1;
    plateau [coord_X][coord_Y]->bat->consommation_elec = CSMA_ELEC_COMMERCE_LV1;
    plateau [coord_X][coord_Y]->bat->image_bat = chargerImage("commerce_lv1.bmp");
    plateau [coord_X][coord_Y]->bat->type = 'i';
    }

void placer_industrie ()
{
    plateau [coord_X][coord_Y]->construction=1;
    plateau [coord_X][coord_Y]->densite=DENS_INDUSTRIE_CTR;
    plateau [coord_X][coord_Y]->hapiness=0;
    plateau [coord_X][coord_Y]->bat->consommation_eau = CSMA_EAU_INDUSTRIE_LV1;
    plateau [coord_X][coord_Y]->bat->consommation_elec = CSMA_ELEC_INDUSTRIE_LV1;
    plateau [coord_X][coord_Y]->bat->image_bat = chargerImage("industrie_lv1.bmp");
    plateau [coord_X][coord_Y]->bat->type = 'i';
}


