#ifndef SAUVEGARDER_H_INCLUDED
#define SAUVEGARDER_H_INCLUDED

void sauver_partie();
void sauvegarde_ville(FILE*fp);
void sauvegarde_plateau(FILE*fp);
void sauvegarde_case(FILE*fp,int i,int j);
void sauvegarde_bat(FILE*fp,int i, int j);

#endif // SAUVEGARDER_H_INCLUDED
