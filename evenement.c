#include "projet.h"

void evenement(t_ville* ville, t_info_BFS* info)
{
    if (horloge.tic)
    {
        update_eau(ville, info);
    }
}
