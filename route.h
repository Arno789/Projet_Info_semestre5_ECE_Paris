#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

t_case* creer_route ();

typedef struct route
{
    int raccord; /// 4 bool�ens idiquant o� se situent les routes  :'0001' juste un raccord par le sud : '1111' limite un rond point � ce niveau l� ...
    int coordx;
    int coordy;
    BITMAP *image;
    int rotation;
}t_route;

typedef struct point    ///Un point sur un plan est d�finit par 2 coordonn�es
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
    t_point* depart;    /// Num�ro de sommet de r�f�rence
    t_point* arrive;    /// Num�ro de sommet d'arriv�
    int** l;            /// Tableau dynamique allou� des longueurs minimales des sommets depuis s
    t_point*** pred;    /// Tableau dynamique allou� des pr�decesseurs sommets
    int clique;   ///Boolen pour que les actions s'effectuent bien dans le bon ordre
} t_info_BFS;

void algorithme (t_ville* ville, t_info_BFS* info);  ///Le fameux et l'unique
void init_info (t_info_BFS* info); ///Allocation et initialisation des info pour l'algo
void reset_info (t_info_BFS* info, t_ville* ville); ///A la fin de l'algorithme suppression (reset) des variable devenues inutiles
void init_tab (t_point* tab [100]); ///Initialisation d'un tableau de 100 points




#endif // ROUTE_H_INCLUDED
