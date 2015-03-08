#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#define SCREEN_LARGEUR 1024
#define SCREEN_HAUTEUR 768

typedef struct horloge
{
    int seconde;
    int minute;
    int heure;
    int jour;
    int mois;
    int an;
    int tic;
    long int clock1;
} t_horloge;

extern BITMAP* buffer;
extern BITMAP* buffer2;
extern BITMAP* horloge_image;
extern BITMAP* image_acceuil;

extern float zoom;
extern float depX, depY;

void initialiser_allegro();
void affichage (BITMAP *image);
BITMAP *chargerImage(char *nomFichierImage);
void afficher_temps_console ();
BITMAP* init_buffer (BITMAP* buffer);
void afficher_matrice ();
void afficher_case_matrice();
void gerer_zoom ();


#endif // AFFICHAGE_H_INCLUDED
