#include "projet.h"

t_ville* ville=NULL;

void init_ville()
{
    ville = malloc(sizeof(t_ville));
    ville->flouz=FLOUZ_INITIAL;
    ville->population=0;
    ville->plateau = malloc(LARGEUR_PLATEAU*sizeof(t_case**));
    for (coord_X=0 ; coord_X<LARGEUR_PLATEAU ; coord_X++)
    {
        ville->plateau [coord_X] = malloc(HAUTEUR_PLATEAU*sizeof(t_case*));
        for (coord_Y=0 ; coord_Y<HAUTEUR_PLATEAU ; coord_Y++)
        {
            //ville->plateau[coord_X][coord_Y] = malloc(sizeof(t_case));
            ville->plateau[coord_X][coord_Y] = init_case();
        }
    }
}
