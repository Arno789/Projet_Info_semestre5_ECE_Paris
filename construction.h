#ifndef CONSTRUCTION_H_INCLUDED
#define CONSTRUCTION_H_INCLUDED


typedef struct construction
{
    short int construction;
    int creation_route;
    t_case* case_a_construire;
}t_construction;


void init_construction (t_construction* construction);
void placement (t_ville* ville, t_construction* construction);
void attriubtion_image_route (t_case* tcase, int raccord);
int detection_route (t_ville* ville, int x, int y);

void placement_route (t_ville* ville, t_info_BFS* info, t_construction* construction);
void clean_construction_route (t_construction* construction);

t_case* creer_maison ();
t_case* creer_commerce ();
t_case* creer_industrie ();
t_case* creer_centrale ();
t_case* creer_chateau ();


#endif // CONSTRUCTION_H_INCLUDED
