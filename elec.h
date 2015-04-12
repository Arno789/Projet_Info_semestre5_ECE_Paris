#ifndef ELEC_H_INCLUDED
#define ELEC_H_INCLUDED

void update_elec (t_ville* ville, t_info_BFS* info);
/// Met a jours à tous les TIC (a toutes les secondes en vitesse normalle) les informations concernant la distribution de l'eau

void algorithme_elec (t_ville* ville, t_info_BFS* info, int capa_totale);
/// Basé sur le BFS, comme les routes, les habitations les plus proche bénéficiront en premier lieu des ressources

void reset_info_elec (t_info_BFS* info, t_ville* ville);
/// On ne reset et free que certaines variable de info_BFS utilsé par l'algo de l'eau

void verification_distrib_elec (t_ville* ville);
/// va checker toutes les cases du terrain pour vérifier si elles sont approvisionnées



#endif // ELEC_H_INCLUDED
