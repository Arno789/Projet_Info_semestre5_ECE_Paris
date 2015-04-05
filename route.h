#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

t_case* creer_route ();

typedef struct route
{
    int raccord; /// 4 booléens idiquant où se situent les routes  :'0001' juste un raccord par le sud : '1111' limite un rond point à ce niveau là ...
    int coordx;
    int coordy;
    BITMAP *image;
    int rotation;
}t_route;

typedef struct point    ///Un point sur un plan est définit par 2 coordonnées
{
    int x;
    int y;
}t_point;

extern BITMAP* im_route_1;
extern BITMAP* im_route_2;
extern BITMAP* im_route_3;
extern BITMAP* im_route_4;
extern BITMAP* im_route_d;

typedef struct info
{
    t_point* depart;    /// Numéro de sommet de référence
    t_point* arrive;    /// Numéro de sommet d'arrivé
    int** l;            /// Tableau dynamique alloué des longueurs minimales des sommets depuis s
    t_point*** pred;    /// Tableau dynamique alloué des prédecesseurs sommets
    int clique;   ///Boolen pour que les actions s'effectuent bien dans le bon ordre
} t_info_BFS;

void algorithme (t_ville* ville, t_info_BFS* info);  ///Le fameux et l'unique
void init_info (t_info_BFS* info); ///Allocation et initialisation des info pour l'algo
void reset_info (t_info_BFS* info, t_ville* ville); ///A la fin de l'algorithme suppression (reset) des variable devenues inutiles
void init_tab (t_point* tab [100]); ///Initialisation d'un tableau de 100 points




#endif // ROUTE_H_INCLUDED
