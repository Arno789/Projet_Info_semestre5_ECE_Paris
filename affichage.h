#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#define SCREEN_LARGEUR 1024
#define SCREEN_HAUTEUR 768
#define TAILLE_CASE 20
#define HAUTEUR_BO_BAT 138
#define HAUTEUR_BO 70


extern BITMAP* buffer;                  /// D�claration en globale de toutes les BITMA�P utilis�es
extern BITMAP* buffer_image;                 ///
extern BITMAP* horloge_image;           ///
extern BITMAP* image_acceuil;           ///
extern BITMAP* image_action_bo;         ///
extern BITMAP* boconst;
extern BITMAP* im_commerce_lv1;
extern BITMAP* im_maison_lv1;
extern BITMAP* im_industrie_lv1;
extern BITMAP* bo_couleur;
extern BITMAP* bo;



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
void affichage_barre_outil ();

void init_buffer_image();
void gerer_buffer_image();


#endif // AFFICHAGE_H_INCLUDED
