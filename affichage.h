#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#define SCREEN_LARGEUR 1024
#define SCREEN_HAUTEUR 768
#define TAILLE_CASE 20
#define HAUTEUR_BO_BAT 138
#define HAUTEUR_BO 70
#define TAILLE_PLT_IMG_W 1244
#define TAILLE_PLT_IMG_H 1008
#define COORD_ORG_PLT_X 120
#define COORD_ORG_PLT_Y 120

extern BITMAP* buffer;                  /// Déclaration en globale de toutes les BITMA¨P utilisées
extern BITMAP* buffer_image;            ///
extern BITMAP* horloge_image;           ///
extern BITMAP* terrain_jeu;             ///
extern BITMAP* image_action_bo;         ///
extern BITMAP* boconst;
extern BITMAP* im_commerce_lv1;
extern BITMAP* im_maison_lv1;
extern BITMAP* im_industrie_lv1;
extern BITMAP* centrale_lv1;
extern BITMAP* bo_couleur;
extern BITMAP* bo;


typedef struct affichage_info
{
    float zoom;             /// Déclaration de la variable zoom, utilisé dans chaque fonction d'affichage
    int depX,depY;          /// Variable indiquant le déplacement de l'image par rapport a l'écran, liée avec le zoom
}t_affichage;

void afficher_ville (t_ville* ville, t_affichage* affichage_info);

void initialiser_allegro();

void init_affichage_info (t_affichage* affichage_info);
void afficher_construction_en_cours (t_ville* ville, t_affichage* affichage_info, t_construction* construction);     ///Affichage de la fonction drag and drop lors d'une construction
void afficher_case_matrice(t_case* tcase, int x, int y, t_affichage* affichage_info);                   ///Affiche une case sur le buffer
void afficher_case_grille_construction (t_ville* ville, int x, int y, t_affichage* affichage_info);


void affichage (t_ville* ville, t_affichage* affichage_info, t_construction* construction); /// Sous programme principal de l'affichage : appel dans l'ordre souhaité de tous les autres SP d'affichage
BITMAP *chargerImage(char *nomFichierImage);    ///SP utilisé pour charger toutes les images
BITMAP* init_buffer (BITMAP* buffer);           ///Utilité limité
void gerer_zoom ();                             ///Calcul le zoom en fct° de la position de la molette
void gerer_deplacement ();                      ///Calcul depX et depY, en fct° du zoom, et le scroll de l'écran
void affichage_barre_outil ();

void init_buffer_image();
void gerer_buffer_image();


#endif // AFFICHAGE_H_INCLUDED
