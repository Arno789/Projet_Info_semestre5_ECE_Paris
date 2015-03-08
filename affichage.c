#include "projet.h"

float zoom=1;
float depX=0, depY=0;
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
    gerer_zoom ();
    clear_bitmap (buffer);
    blit (image, buffer, 0,0,0,0, SCREEN_W, SCREEN_H);
    afficher_temps_allegro ();
    afficher_matrice ();
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

void afficher_matrice ()
{
    for (coord_X=0 ; coord_X < LARGEUR_PLATEAU ; coord_X++)
    {
        for (coord_Y=0 ; coord_Y < HAUTEUR_PLATEAU ; coord_Y++)
            {
                //printf ("%d\t%d\n", coord_X, coord_Y);
                afficher_case_matrice();
            }
    }
}

void afficher_case_matrice()
{
    int x1, y1, x2, y2;
    x1 = 20*coord_X*zoom;
    y1 = 20*coord_Y*zoom;
    x2 = (20*(coord_X+1))*zoom;
    y2 = (20*(coord_Y+1))*zoom;

    /*if (plateau [coord_X] [coord_Y]->bat&&plateau [coord_X] [coord_Y]->bat->image_bat)
        draw_sprite (buffer, plateau [coord_X] [coord_Y]->bat->image_bat, 20*coord_X , 20*coord_Y);*/
    if ((coord_X+coord_Y)%2)
        rectfill(buffer, x1, y1,x2, y2, makecol (200,100,100));
}


 void gerer_zoom ()
 {

      if (zoom == 1)      ///pour éviter les légers décalages apres avoir zoomé puis dé zoomé
        {
            depX=0;
            depY=0;
        }

        if (mouse_z<0) mouse_z=0;                   /// on ne veut pas dezoomer
        zoom = 1 + mouse_z*0.3;                     /// la valeur du zoom dépend de la molette de la souris

/*
    if (key[KEY_ALT])
        {
            depX = depX - mouse_depx/zoom;    ///Déplacement du dessin (quand on a zoomé) en maintenant Alt enfoncé
            depY = depY - mouse_depy/zoom;
            printf ("%f\n", depX);
        }*/
 }
