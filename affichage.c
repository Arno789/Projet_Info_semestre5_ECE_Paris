#include "projet.h"

BITMAP* buffer=NULL;
BITMAP* buffer_image=NULL;
BITMAP* terrain_jeu=NULL;
BITMAP* horloge_image = NULL;
BITMAP* image_action_bo = NULL;
BITMAP* boconst = NULL;
BITMAP* bo = NULL;
BITMAP* bo_couleur = NULL;
BITMAP* im_commerce_lv1=NULL;
BITMAP* im_maison_lv1=NULL;
BITMAP* im_industrie_lv1=NULL;
BITMAP* centrale_lv1 = NULL;

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

void init_affichage_info (t_affichage* affichage_info)
{
    affichage_info->depX = 0;
    affichage_info->depY = 0;
    affichage_info->zoom = 1;
}

void affichage (t_ville* ville, t_affichage* affichage_info, t_construction* construction)
{
    gerer_zoom (affichage_info);
    clear_bitmap (buffer);

    if (affichage_info->zoom>=1) ///Affichage du fond d'écran du plateu de jeu
        stretch_blit(terrain_jeu, buffer, affichage_info->depX+COORD_ORG_PLT_X, affichage_info->depY+COORD_ORG_PLT_Y, SCREEN_W/affichage_info->zoom, SCREEN_H/affichage_info->zoom, 0,0, SCREEN_W, SCREEN_H);
    else stretch_blit(terrain_jeu, buffer, 0, 0, TAILLE_PLT_IMG_W, TAILLE_PLT_IMG_H, 6,6, (SCREEN_W+290)*affichage_info->zoom, (SCREEN_H+310)*affichage_info->zoom);

    afficher_ville (ville, affichage_info);

    afficher_construction_en_cours (ville, affichage_info, construction);

    if (!construction->construction)
        affichage_barre_outil();

    if (key[KEY_B])
        blit (buffer_image, buffer, 0, 0,0,0, SCREEN_W, SCREEN_H);
    actualiser_coord (ville, affichage_info);//stretch_blit(buffer, screen, depX, depY, zoom*SCREEN_W, zoom*SCREEN_H, 0, 0, SCREEN_W, SCREEN_H);
    afficher_temps_allegro ();
    blit (buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
}

void afficher_terrain ()
{
    //stretch_blit(terrain_jeu, buffer, depX+COORD_ORG_PLT_X, depY+COORD_ORG_PLT_Y, SCREEN_W/zoom, SCREEN_H/zoom, 0,0, SCREEN_W, SCREEN_H);
}

void affichage_barre_outil ()
{
    masked_blit(bo, buffer, 0, 0, 0, SCREEN_H+0-HAUTEUR_BO, SCREEN_W, SCREEN_H);
    if (test_constru)
        masked_blit(boconst, buffer, 0, 0, 0, SCREEN_H-HAUTEUR_BO_BAT+0, SCREEN_W, SCREEN_H);
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

void init_image()
{
    im_commerce_lv1=chargerImage("commerce_lv1.bmp");
    im_maison_lv1=chargerImage("maison_lv1.bmp");
    im_industrie_lv1=chargerImage("industrie_lv1.bmp");
    bo = chargerImage("barre_outils.bmp");
    bo_couleur = chargerImage("barre_outils_couleur.bmp");
    centrale_lv1 = chargerImage ("centrale_lv1.bmp");
}

void init_buffer_image()
{
    buffer_image = create_bitmap(SCREEN_W,SCREEN_H);
}

void gerer_buffer_image()
{
    clear_bitmap (buffer_image);
    blit (bo_couleur, buffer_image, 0, 0, 0, SCREEN_H-HAUTEUR_BO, SCREEN_W, SCREEN_H);
    if (test_constru)
        blit (image_action_bo, buffer_image, 0, 0, 0, SCREEN_H-HAUTEUR_BO_BAT, SCREEN_W, SCREEN_H);
}


void gerer_zoom (t_affichage* affichage_info)
{
    if (mouse_z<-3) mouse_z=-3;                   /// on ne veut pas dezoomer
    if (mouse_z>20) mouse_z=20;
    affichage_info->zoom = 1 + mouse_z*0.3;                     /// la valeur du zoom dépend de la molette de la souris
    /*f (key[KEY_PGDN])
        affichage_info->zoom = affichage_info->zoom-0.1;
    if (key[KEY_PGUP])                 ///Zoom géré au clavier OU à la souris.
        affichage_info->zoom = affichage_info->zoom+0.1;*/
    if (affichage_info->zoom < 0.1)
        affichage_info->zoom = 0.1;
    if (affichage_info->zoom > 10)
        affichage_info->zoom = 10;
    gerer_deplacement (affichage_info);
}

void gerer_deplacement (t_affichage* affichage_info)
{
    if (mouse_x<10)
    {
        affichage_info->depX = affichage_info->depX-2*(10-mouse_x);
    }
    if (mouse_y<10)
    {
        affichage_info->depY = affichage_info->depY-2*(10-mouse_y);
    }

    if (mouse_x>(SCREEN_W-10))
    {
        affichage_info->depX = affichage_info->depX+2*(mouse_x-(SCREEN_W-10));
    }
    if (mouse_y>(SCREEN_H-10))
    {
        affichage_info->depY = affichage_info->depY+2*(mouse_y-(SCREEN_H-10));
    }

    if (affichage_info->depX>SCREEN_W+100-SCREEN_W/affichage_info->zoom)
        affichage_info->depX=SCREEN_W+100-SCREEN_W/affichage_info->zoom;
    if (affichage_info->depY>SCREEN_H+COORD_ORG_PLT_Y-SCREEN_H/affichage_info->zoom)
        affichage_info->depY=SCREEN_H+COORD_ORG_PLT_Y-SCREEN_H/affichage_info->zoom;
    if (affichage_info->depX<-COORD_ORG_PLT_X)
        affichage_info->depX=-COORD_ORG_PLT_X;
    if (affichage_info->depY<-COORD_ORG_PLT_Y)
        affichage_info->depY=-COORD_ORG_PLT_Y;
}


