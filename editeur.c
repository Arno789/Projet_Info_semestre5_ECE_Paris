#include "projet.h"

int coord_X, coord_Y;
char touche;
char bouton;
int mouse_click;
int mouse_unclick;
int key_press[KEY_MAX];
int key_unpress[KEY_MAX];


int mouse_depx;
int mouse_depy;

void traitement_clique (t_ville* ville, t_construction* construction)
{
    gerer_buffer_image();
    actualiser_coord ();
    int col=-1;
    if (mouse_click && !construction->construction)
    {
        col=getpixel (buffer_image, mouse_x, mouse_y);
        mouse_click=0;
        printf("%d\n",col);
    }
    switch (col)
    {
    case 0x00c800:
        printf("mode construction\n");
        if (!test_constru)
            test_constru=1;
        else if (test_constru)
            test_constru=0;
        break;
    case 0x007f7f:
        printf ("maison\n");
        construction->construction=1;
        construction->case_a_construire= creer_maison();
        break;
    case 0xc80000:
        construction->construction=1;
        test_constru=0;
        construction->case_a_construire= creer_route();
        break;
    case 0x0000c8:
        printf("centrale elec\n");
        construction->construction=1;
        construction->case_a_construire= creer_centrale();
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
        placement(ville, construction);
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
