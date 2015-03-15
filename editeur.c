#include "projet.h"

t_case* plateau [LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
int coord_X, coord_Y;
char touche;
char bouton;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];
t_action* action;
t_construction* construction;

int mouse_depx;
int mouse_depy;

void init_construction ()
{
    construction = malloc(sizeof (t_construction));
    construction->case_a_construire=NULL;
    construction->construction=0;
}


void init_action ()
{
    action = malloc (sizeof (t_action));
    action->construction_autre=0;
    action->construction_caserne=0;
    action->construction_centrale_elec=0;
    action->construction_chateau_eau=0;
    action->construction_commerce=0;
    action->construction_commico=0;
    action->construction_hopital=0;
    action->construction_industrie=0;
    action->construction_maison=0;
}
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
    ///case_cree->bat->image_bat = chargerImage("commerce_lv1.bmp");
    case_cree->bat->image_bat = NULL;
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
    ///case_cree->bat->image_bat = chargerImage("industrie_lv1.bmp");
    case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'i';
    return case_cree;
}

void placement ()
{
    if (!plateau [coord_X][coord_Y]->construction)
        {
            if (construction->case_a_construire->bat->image_bat)
                stretch_sprite(screen, construction->case_a_construire->bat->image_bat, TAILLE_CASE*coord_X*zoom, TAILLE_CASE*coord_Y*zoom, TAILLE_CASE*zoom, TAILLE_CASE*zoom);
            if (mouse_click)
                {
                    plateau [coord_X][coord_Y]=construction->case_a_construire;
                    construction->construction=0;
                }
        }


}
void traitement_clique ()
{
    coord_X=mouse_x/TAILLE_CASE;
    coord_Y=mouse_y/TAILLE_CASE;
    int col=-1;
    if (mouse_click)
        col=getpixel (image_action_bo, mouse_x, mouse_y);
    mouse_click=0;
    switch (col)
    {
    case 0x000000:
        printf("0,0,0\n");
        break;
    case 0xff0000:
        printf ("maison\n");
        construction->construction=1;
        construction->case_a_construire= creer_maison();
        break;
    case 0xffff00:
        printf("255,255,0\n");
        break;
    case 0xff00ff:
        printf("255,0,255\n");
        break;
    case 0x00ffff:
        printf("0,255,255\n");
        break;
    case 0x00ff00:
        printf ("commerce\n");
        construction->construction=1;
        construction->case_a_construire = creer_commerce();
        break;
    case 0x0000ff:
        printf ("industrie\n");
        construction->construction=1;
        construction->case_a_construire = creer_industrie();
        break;
    }
    if (construction->construction)
        placement();

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
