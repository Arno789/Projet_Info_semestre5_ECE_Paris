#ifndef SAUVEGARDER_H_INCLUDED
#define SAUVEGARDER_H_INCLUDED

void sauver_partie(t_ville* ville);
void sauvegarde_ville(FILE*fp, t_ville* ville);
void sauvegarde_plateau(FILE*fp, t_ville* ville);
void sauvegarde_case(FILE*fp, int i,int j, t_ville* ville);
void sauvegarde_bat(FILE*fp, int i, int j, t_ville* ville);

#endif // SAUVEGARDER_H_INCLUDED
