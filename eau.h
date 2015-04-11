#ifndef EAU_H_INCLUDED
#define EAU_H_INCLUDED

void update_eau (t_ville* ville, t_info_BFS* info);
void algorithme_eau (t_ville* ville, t_info_BFS* info, int capa_totale);
void reset_info_eau (t_info_BFS* info, t_ville* ville);
void reset_marqueur_route (t_ville* ville);
void verification_distrib_eau (t_ville* ville);
#endif // EAU_H_INCLUDED
