#ifndef ELEC_H_INCLUDED
#define ELEC_H_INCLUDED

void update_elec (t_ville* ville, t_info_BFS* info);
/// Met a jours � tous les TIC (a toutes les secondes en vitesse normalle) les informations concernant la distribution de l'eau

void algorithme_elec (t_ville* ville, t_info_BFS* info, int capa_totale);
/// Bas� sur le BFS, comme les routes, les habitations les plus proche b�n�ficiront en premier lieu des ressources

void reset_info_elec (t_info_BFS* info, t_ville* ville);
/// On ne reset et free que certaines variable de info_BFS utils� par l'algo de l'eau

void verification_distrib_elec (t_ville* ville);
/// va checker toutes les cases du terrain pour v�rifier si elles sont approvisionn�es



#endif // ELEC_H_INCLUDED
