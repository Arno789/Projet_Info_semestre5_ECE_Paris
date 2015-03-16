#ifndef CHARGER_H_INCLUDED
#define CHARGER_H_INCLUDED

void charger_partie();
void charger_ville(FILE*fp);
void charger_plateau(FILE*fp);
void charger_case(FILE*fp);
void charger_bat(FILE*fp,int i, int j);

#endif // CHARGER_H_INCLUDED
