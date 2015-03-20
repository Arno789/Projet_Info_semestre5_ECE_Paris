#ifndef CONSTRUCTION_H_INCLUDED
#define CONSTRUCTION_H_INCLUDED


typedef struct construction
{
    short int construction;
    t_case* case_a_construire;
}t_construction;


void init_construction (t_construction* construction);
void placement (t_ville* ville, t_construction* construction);

t_case* creer_maison ();
t_case* creer_commerce ();
t_case* creer_industrie ();


#endif // CONSTRUCTION_H_INCLUDED
