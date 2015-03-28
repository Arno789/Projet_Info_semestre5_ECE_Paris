#ifndef VILLE_H_INCLUDED
#define VILLE_H_INCLUDED

#define FLOUZ_INITIAL 200000
///struct CONSTRUCTION
/*
 structure regroupant les batiments "clefs en main" comme les casernes et les chateau d'eau
 ainsi que les terrains vagues qui evoluent
 t_contruction contient leurs APPROVISIONNEMENT, leur TYPE (terrain vague, caserne, chateau, route...)
 et leur STADE de construction (Terrain vague (0 habitant) ou Ruine en cas de r�gression (0 habitant)- Cabane (10 habitants)- Maison (50 habitants)- Immeuble (100 habitants)- Gratte-ciel (1000 habitants)
*/
typedef struct bat
{
    BITMAP* image_bat;
    int consommation_eau;
    int consommation_elec;
    char type;
    int taille;
}t_bat;


typedef struct tcase
{
    int hapiness;   /// Non obligatoire, � utiliser plus tard
    int densite;    /// Population vivant dans le bat en question
    t_bat* bat;     /// On link la structure bat, contenant les infos propre au bat
    short int construction ; ///Bool�en : Est ce qu'il y a un batiment / construction sur cette case ?
}t_case;
///struct CASE
/*
�l�ment de base du PLATEAU : contient les infos de la case comme le bonheur, la densit�, la CONSTRUCTION
*/

///struct VILLE
/*
La VILLE regroupe toutes les �l�ments et informations de la ville :
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
    int **plan_construction; //tableau de int qui indique si les cases sont bonnes pour la construction : 0 pour un imcapcit� de construire, 1 pour un terrai d�gag�, et 2 pour la proximit� a une route (obligatoire pour la construction);
    int flouz;
    int coord_X;
    int coord_Y;
}t_ville;


void init_ville(t_ville* ville);

              ///Appelle de facon optimis� le sous programme d'affichage de case.


#endif // VILLE_H_INCLUDED
