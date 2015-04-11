#ifndef VILLE_H_INCLUDED
#define VILLE_H_INCLUDED

#define FLOUZ_INITIAL 200000
///struct CONSTRUCTION
/*
 structure regroupant les batiments "clefs en main" comme les casernes et les chateau d'eau
 ainsi que les terrains vagues qui evoluent
 t_construction contient leurs APPROVISIONNEMENT, leur TYPE (terrain vague, caserne, chateau, route...)
 et leur STADE de construction (Terrain vague (0 habitant) ou Ruine en cas de régression (0 habitant)- Cabane (10 habitants)- Maison (50 habitants)- Immeuble (100 habitants)- Gratte-ciel (1000 habitants)
*/


typedef struct point    ///Un point sur un plan est définit par 2 coordonnées
{
    int x;
    int y;
}t_point;


typedef struct bat
{
    char type;
    int niveau;

    BITMAP* image_bat;
    int rotation;
    int consommation_eau;
    int consommation_elec;
    int taille_x;
    int taille_y;
} t_bat;


typedef struct tcase
{
    int hapiness;   /// Non obligatoire, à utiliser plus tard
    int densite;    /// Population vivant dans le bat en question
    t_bat* bat;     /// On link la structure bat, contenant les infos propre au bat
    short int construction ; ///Booléen : Est ce qu'il y a un batiment / construction sur cette case ?
    int marqueur;
    int appro_eau; /// Quantité d'eau que la case recoit des chateaux d'eau, est géré la l'algo des chateau d'eau normalement appro_eau == csmation_eau
    int appro_elec;

    t_point* parent;
} t_case;
///struct CASE
/*
élément de base du PLATEAU : contient les infos de la case comme le bonheur, la densité, la CONSTRUCTION
*/

///struct VILLE
/*
La VILLE regroupe toutes les éléments et informations de la ville :
    - la population totale
    - le PLATEAU contenant toutes les CASES de la VILLE
    - le FLOUZ qui est le solde de monnaie
*/
typedef struct ville
{
    int population;
    t_case*** plateau;
    int **gestion_eau;
    int **gestion_elec;
    int **plan_construction; //tableau de int qui indique si les cases sont bonnes pour la construction : 0 pour un imcapcité de construire, 1 pour un terrai dégagé, et 2 pour la proximité a une route (obligatoire pour la construction);
    int flouz;
    int coord_X;
    int coord_Y;
    int prec_X;
    int prec_Y;
    int changement_case;
} t_ville;


void init_ville(t_ville* ville);
//void init_info (t_info_BFS* info_BFS);  ///Allocation et initialisation des info pour l'algo



#endif // VILLE_H_INCLUDED
