#include "projet.h"


void initialiser_allegro()
{
    allegro_init();
    install_keyboard();
    set_keyboard_rate(0,0);
    install_mouse();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_LARGEUR,SCREEN_HAUTEUR,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);

}

void affichage (BITMAP *image)
{
    clear_bitmap (buffer);
    blit (image, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    afficher_temps_allegro ();
    blit (buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}

BITMAP* init_buffer (BITMAP* buffer)
{
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    return (buffer);
}

BITMAP *chargerImage(char *nomFichierImage)
{
    BITMAP *bmp;
    bmp=load_bitmap(nomFichierImage,NULL);
    if (bmp==NULL)
    {
        allegro_message("pas pu trouver/charger %s",nomFichierImage);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    printf("Image charg\202e : %s\n", nomFichierImage);
    return bmp;
}

void afficher_temps_console ()
{
    printf("%d/%d/%d %d:%d:%d\n", horloge.jour, horloge.mois, horloge.an, horloge.heure, horloge.minute, horloge.seconde);
}


