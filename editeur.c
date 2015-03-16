#include "projet.h"

//t_case* plateau [LARGEUR_PLATEAU][HAUTEUR_PLATEAU];
int coord_X, coord_Y;
char touche;
char bouton;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];


int mouse_depx;
int mouse_depy;

void traitement_clique ()
{
    coord_X=mouse_x/TAILLE_CASE;
    coord_Y=mouse_y/TAILLE_CASE;
    int col=-1;
    if (mouse_click && !construction->construction)
    {
        col=getpixel (image_action_bo, mouse_x, mouse_y);
        mouse_click=0;
    }
    switch (col)
    {
    case 0x000000:
        printf("0,0,0\n");
        break;
    case 0x007f7f:
        printf ("maison\n");
        construction->construction=1;
        construction->case_a_construire= creer_maison();
        break;
    case 0xffff00:
        construction->construction=1;
        construction->case_a_construire= creer_route();
        break;
    case 0xff00ff:
        printf("255,0,255\n");
        break;
    case 0x00ffff:
        printf("0,255,255\n");
        break;
    case 0x7fff00:
        printf ("commerce\n");
        construction->construction=1;
        construction->case_a_construire = creer_commerce();
        break;
    case 0xff56ff:
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
