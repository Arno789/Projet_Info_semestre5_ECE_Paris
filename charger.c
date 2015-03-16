#include "projet.h"


void charger_bat(FILE*fp,int i, int j)
{
    fscanf(fp,"        consommation_eau : %d\n",&(ville->plateau[i][j]->bat->consommation_eau));
    fscanf(fp,"        consommation_elec : %d\n\n",&(ville->plateau[i][j]->bat->consommation_elec));
    //fscanf(fp,"        rejet_dechet : %d\n\n",&(ville->plateau[i][j]->bat->rejet_dechet));
    //fscanf(fp,"        rejet_pollution : %d\n\n",&(ville->plateau[i][j]->bat->rejet_pollution));
    ///image??
    fscanf(fp,"        type : %d\n",&(ville->plateau[i][j]->bat->type));
}

void charger_case(FILE*fp)
{
    int i,j;

    fscanf(fp,"    CASE [%d][%d]",&i,&j);
    fscanf(fp,"        hapiness : %d\n",&(ville->plateau[i][j]->hapiness));
    fscanf(fp,"        densite : %d\n",&(ville->plateau[i][j]->densite));
    fscanf(fp,"        construction : %hd\n",&(ville->plateau[i][j]->construction));
    if (ville->plateau[i][j]->bat != NULL) charger_bat(fp,i,j);
}

void charger_plateau(FILE*fp)
{
    int i,j;

    for (i=0;i<LARGEUR_PLATEAU;i++)
    {
        for (j=0;j<HAUTEUR_PLATEAU;j++)
        {
            if (ville->plateau[i][j] != NULL) charger_case(fp);
        }
    }
}

void charger_ville(FILE*fp)
{
    fscanf(fp,"population : %d\n",&(ville->population));
    fscanf(fp,"flouz : %d\n",&(ville->flouz));
    charger_plateau(fp);
}

void charger_partie()
{
    FILE* fp=NULL;
    BITMAP *buffer_sauv=NULL;
    int i;

    char nom[56];   //les 5 lettres de .carl et le \0

    buffer_sauv=create_bitmap(SCREEN_LARGEUR,SCREEN_HAUTEUR);

    for (i=0; i<57; i++)
    {
        nom[i]= '\0';
    }

    do
    {
        ///raffraichir clavier
        rafraichir_clavier_souris();

        ///gestion des touches
        if (touche=='\b')
        {
            if (strlen(nom)>0)
            {
                ///effacer la dernère lettre
                nom[strlen(nom)-1]='\0';
            }

        }
        else if (touche!='\0' && touche>='A')
        {
            ///ajouter la lettre au nom de fichier
            strcat(nom,&touche);
        }

        ///actualisation de l'affichage
        clear_bitmap(buffer_sauv);
        textprintf_centre_ex(buffer_sauv, font, SCREEN_W / 2, 120,makecol(0, 100, 243), -1,"ENTRER LE NOM DE LA SAUVEGARDE : %s.carl\n50lettres maxi\n",nom);
        blit(buffer_sauv,screen, 0, 0, 0, 0,SCREEN_LARGEUR, SCREEN_HAUTEUR);
    }
    while (!key[KEY_ENTER] && strlen(nom)<50);

    ///ajout du .carl
    strcat(nom,".carl");

    fp=fopen(nom,"r");
    if (fp != NULL)// On peut lire et écrire dans le fichier
    {
        init_ville();
        fscanf(fp,"Partie sauvegardee le ...\n");
        charger_ville(fp);
    }
    else// On affiche un message d'erreur si on veut
    {
        printf("Erreur de lecture du fichier");
    }

    fclose(fp);
}
