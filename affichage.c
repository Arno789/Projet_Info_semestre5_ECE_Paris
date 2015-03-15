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
    blit (buffer, screen, depX, depY,0,0, SCREEN_W, SCREEN_H);
}

BITMAP* init_buffer (BITMAP* buffer)
{
    buffer = create_bitmap(7*SCREEN_W,7*SCREEN_H);
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
    x1 = TAILLE_CASE*coord_X*zoom;
    y1 = TAILLE_CASE*coord_Y*zoom;
    x2 = (TAILLE_CASE*(coord_X+1))*zoom;
    y2 = (TAILLE_CASE*(coord_Y+1))*zoom;

    if (plateau [coord_X] [coord_Y]->bat&&plateau [coord_X] [coord_Y]->bat->image_bat)
        stretch_sprite(buffer, plateau [coord_X] [coord_Y]->bat->image_bat, TAILLE_CASE*coord_X*zoom, TAILLE_CASE*coord_Y*zoom, TAILLE_CASE*zoom, TAILLE_CASE*zoom);
    ///draw_sprite (buffer, plateau [coord_X] [coord_Y]->bat->image_bat, 20*coord_X , 20*coord_Y);
    else if ((coord_X+coord_Y)%2)
        rectfill(buffer, x1, y1,x2, y2, makecol (100,200,100));
}


void gerer_zoom ()
{

    if (zoom == 1)      ///pour �viter les l�gers d�calages apres avoir zoom� puis d� zoom�
    {
        depX=0;
        depY=0;
    }

    if (mouse_z<0) mouse_z=0;                   /// on ne veut pas dezoomer
    if (mouse_z>20) mouse_z=20;
    zoom = 1 + mouse_z*0.3;                     /// la valeur du zoom d�pend de la molette de la souris
    gerer_deplacement ();
}

void gerer_deplacement ()
{
    if (mouse_x<10)
    {
        depX=depX-2*(10-mouse_x);
    }
    if (mouse_y<10)
    {
        depY=depY-2*(10-mouse_y);
    }

    if (mouse_x>1014)
    {
        depX=depX+2*(mouse_x-1014);
    }
    if (mouse_y>758)
    {
        depY=depY+2*(mouse_y-758);
    }

    if (depX>LARGEUR_PLATEAU*TAILLE_CASE*zoom+30-SCREEN_W)
        depX=LARGEUR_PLATEAU*TAILLE_CASE*zoom+30-SCREEN_W;
    if (depY>HAUTEUR_PLATEAU*TAILLE_CASE*zoom+30-SCREEN_H)
        depY=HAUTEUR_PLATEAU*TAILLE_CASE*zoom+30-SCREEN_H;
    if (depX<0)
        depX=0;
    if (depY<0)
        depY=0;

}
