#include "projet.h"

t_case* plateau [LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
int coord_X, coord_Y;
char touche;
char bouton;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];

int mouse_depx;
int mouse_depy;


void init_plateau ()
{
    for (coord_X=0; coord_X<LARGEUR_PLATEAU ; coord_X++)
    {
        for (coord_Y=0; coord_Y<HAUTEUR_PLATEAU ; coord_Y++)
        {
            plateau [coord_X][coord_Y] = malloc(sizeof(t_case));
            plateau [coord_X][coord_Y]->bat = malloc(sizeof(t_bat));
            plateau [coord_X][coord_Y]->construction=0;
            plateau [coord_X][coord_Y]->densite=0;
            plateau [coord_X][coord_Y]->hapiness=0;
            plateau [coord_X][coord_Y]->bat->consommation_eau=0;
            plateau [coord_X][coord_Y]->bat->consommation_elec=0;
            plateau [coord_X][coord_Y]->bat->image_bat=NULL;
            plateau [coord_X][coord_Y]->bat->type='n';
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


void rafraichir_clavier_souris()
{
    static int mouse_prev, mouse_now;
    static int key_prev[KEY_MAX], key_now[KEY_MAX];
    int k;

    mouse_prev = mouse_now;
    mouse_now = mouse_b;
    mouse_click = mouse_now & ~mouse_prev;
    mouse_unclick = ~mouse_now & mouse_prev;

    bouton = '\0';
    if (mouse_click&1)
        bouton = 'g';
    if (mouse_click&2)
        bouton = 'd';
    if (mouse_click&4)
        bouton = 'm';

    for (k=0; k<KEY_MAX; k++)
    {
        key_prev[k] = key_now[k];
        key_now[k] = key[k];
        key_press[k] = key_now[k] && !key_prev[k];
        key_unpress[k] = !key_now[k] && key_prev[k];
    }

    touche = '\0';
    while (keypressed())
        touche = (char)readkey();

    get_mouse_mickeys(&mouse_depx, &mouse_depy);
}
