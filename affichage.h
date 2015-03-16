#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#define SCREEN_LARGEUR 800
#define SCREEN_HAUTEUR 600
#define TAILLE_CASE 20


extern BITMAP* buffer;                  /// D�claration en globale de toutes les BITMA�P utilis�es
extern BITMAP* buffer2;                 ///
extern BITMAP* horloge_image;           ///
extern BITMAP* image_acceuil;           ///
extern BITMAP* image_action_bo;         ///
extern BITMAP* boconst;                 ///

extern float zoom;              /// D�claration de la variable zoom, utilis� dans chaque fonction d'affichage
extern float depX, depY;        /// Variable indiquant le d�placement de l'image par rapport a l'�cran, li�e avec le zoom

void initialiser_allegro();
void affichage (BITMAP *image); /// Sous programme principal de l'affichage : appel dans l'ordre souhait� de tous les autres SP d'affichage
BITMAP *chargerImage(char *nomFichierImage);    ///SP utilis� pour charger toutes les images
void afficher_temps_console ();                 ///Explicite ?
BITMAP* init_buffer (BITMAP* buffer);           ///Utilit� limit�
void afficher_matrice ();                       ///Appelle en boucle (taille du tab) le SP suivant :
void afficher_case_matrice();                   ///Affiche une case sur le buffer
void gerer_zoom ();                             ///Calcul le zoom en fct� de la position de la molette
void gerer_deplacement ();                      ///Calcul depX et depY, en fct� du zoom, et le scroll de l'�cran
void afficher_construction_en_cours ();         ///Affichage de la fonction drag and drop lors d'une construction


#endif // AFFICHAGE_H_INCLUDED
