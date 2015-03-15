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

typedef struct action
{
    int construction_maison;
    int construction_commerce;
    int construction_industrie;
    int construction_caserne;
    int construction_commico;
    int construction_hopital;
    int construction_chateau_eau;
    int construction_centrale_elec;
    int construction_autre;
}t_action;


extern char touche;


extern char bouton;

extern t_action* action;

extern int mouse_click;


extern int mouse_unclick;


extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];


extern int mouse_depx;
extern int mouse_depy;


extern t_case* plateau[LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
extern int coord_X, coord_Y;

void init_plateau();
void rafraichir_clavier_souris();


#endif // EDITEUR_H_INCLUDED
