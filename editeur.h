#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED
#define LARGEUR_PLATEAU 45
#define HAUTEUR_PLATEAU 35

#define DENS_MAISON_CTR 0
#define CSMA_EAU_MAISON_LV1 0
#define CSMA_ELEC_MAISON_LV1 0

#define DENS_COMMERCE_CTR 0
#define CSMA_EAU_COMMERCE_LV1 0
#define CSMA_ELEC_COMMERCE_LV1 0

#define DENS_INDUSTRIE_CTR 0
#define CSMA_EAU_INDUSTRIE_LV1 0
#define CSMA_ELEC_INDUSTRIE_LV1 0

typedef struct bat
{
    int consommation_eau;
    int consommation_elec;
    ///int rejet_dechet;
    ///int rejet_pollution;
    BITMAP* image_bat;
    char type;
}t_bat;

typedef struct tcase
{
    int hapiness;
    int densite;
    t_bat* bat;
    short int construction;
}t_case;


extern t_case* plateau[LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
extern int coord_X, coord_Y;
#endif // EDITEUR_H_INCLUDED
