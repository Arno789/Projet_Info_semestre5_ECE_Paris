#ifndef EAU_H_INCLUDED
#define EAU_H_INCLUDED

void update_eau (t_ville* ville, t_info_BFS* info);
/// Met a jours � tous les TIC (a toutes les secondes en vitesse normalle) les informations concernant la distribution de l'eau

void algorithme_eau (t_ville* ville, t_info_BFS* info, int capa_totale);
/// Bas� sur le BFS, comme les routes, les habitations les plus proche b�n�ficiront en premier lieu des ressources

void reset_info_eau (t_info_BFS* info, t_ville* ville);
/// On ne reset et free que certaines variable de info_BFS utils� par l'algo de l'eau

void reset_marqueur_route (t_ville* ville);
/// On ne reset que les marqueurs sur les routes, pas sur les batiments

void verification_distrib_eau (t_ville* ville);
/// va checker toutes les cases du terrain pour v�rifier si elles sont approvisionn�es


#endif // EAU_H_INCLUDED
