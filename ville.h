#ifndef VILLE_H_INCLUDED
#define VILLE_H_INCLUDED

#define FLOUZ_INITIAL 200000
///struct CONSTRUCTION
/*
 structure regroupant les batiments "clefs en main" comme les casernes et les chateau d'eau
 ainsi que les terrains vagues qui evoluent
 t_contruction contient leurs APPROVISIONNEMENT, leur TYPE (terrain vague, caserne, chateau, route...)
 et leur STADE de construction (Terrain vague (0 habitant) ou Ruine en cas de régression (0 habitant)- Cabane (10 habitants)- Maison (50 habitants)- Immeuble (100 habitants)- Gratte-ciel (1000 habitants)
*/
typedef struct bat
{
    int consommation_eau;
    int consommation_elec;
    ///int rejet_dechet;
    ///int rejet_pollution;
    BITMAP* image_bat;
    char type;
}t_bat;


typedef struct tcase
{
    int hapiness;   /// Non obligatoire, à utiliser plus tard
    int densite;    /// Population vivant dans le bat en question
    t_bat* bat;     /// On link la structure bat, contenant les infos propre au bat
    short int construction ; ///Booléen : Est ce qu'il y a un batiment / construction sur cette case ?
}t_case;
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
    int flouz;
    int coord_X;
    int coord_Y;
}t_ville;


void init_ville(t_ville* ville);

              ///Appelle de facon optimisé le sous programme d'affichage de case.


#endif // VILLE_H_INCLUDED
