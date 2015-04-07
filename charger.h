#ifndef CHARGER_H_INCLUDED
#define CHARGER_H_INCLUDED

void charger_partie(t_ville* ville);
void charger_ville(FILE*fp, t_ville* ville);
void charger_plateau(FILE*fp, t_ville* ville);
void charger_case(FILE*fp, t_ville* ville);
void charger_bat(FILE*fp,int i, int j, t_ville* ville);

#endif // CHARGER_H_INCLUDED
