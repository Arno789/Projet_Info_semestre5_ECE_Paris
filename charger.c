#include "projet.h"


void charger_bat(FILE*fp, int i, int j, t_ville* ville)
{
    int x,y;
    fscanf(fp,"        consommation_eau : %d\n",&(ville->plateau[i][j]->bat->consommation_eau));
    fscanf(fp,"        consommation_elec : %d\n\n",&(ville->plateau[i][j]->bat->consommation_elec));
    //fscanf(fp,"        rejet_dechet : %d\n\n",&(ville->plateau[i][j]->bat->rejet_dechet));
    //fscanf(fp,"        rejet_pollution : %d\n\n",&(ville->plateau[i][j]->bat->rejet_pollution));
    ///image??
    fscanf(fp,"        type : %c\n",&(ville->plateau[i][j]->bat->type));

    switch (ville->plateau[i][j]->bat->type)
    {
    case 'm' :
        ville->plateau[i][j]->bat->image_bat = im_maison_lv1;
        ville->plateau[i][j]->bat->rotation = 0;
        ville->plateau[i][j]->bat->taille_x = 3;
        ville->plateau[i][j]->bat->taille_y = 3;
        break;
    case 'c' :
        ville->plateau[i][j]->bat->image_bat = im_commerce_lv1;
        ville->plateau[i][j]->bat->rotation = 0;
        ville->plateau[i][j]->bat->taille_x = 3;
        ville->plateau[i][j]->bat->taille_y = 3;
        break;
    case 'i' :
        ville->plateau[i][j]->bat->image_bat = im_industrie_lv1;
        ville->plateau[i][j]->bat->rotation = 0;
        ville->plateau[i][j]->bat->taille_x = 3;
        ville->plateau[i][j]->bat->taille_y = 3;
        break;
    case 'e' :
        ville->plateau[i][j]->bat->image_bat = im_centrale_lv1;
        ville->plateau[i][j]->bat->rotation = 0;
        ville->plateau[i][j]->bat->taille_x = 4;
        ville->plateau[i][j]->bat->taille_y = 6;
        break;
    case 'o' :

        ville->plateau[i][j]->bat->image_bat = im_chateau_lv1;
        ville->plateau[i][j]->bat->rotation = 0;
        ville->plateau[i][j]->bat->taille_x = 4;
        ville->plateau[i][j]->bat->taille_y = 6;
        break;
    }
    for (x=i ; x < i+ville->plateau[i][j]->bat->taille_x ; x++)
        for (y=j; y < j +ville->plateau[i][j]->bat->taille_y ; y++)
        {
            if (!ville->plateau[x][y]->parent)
                ville->plateau[x][y]->parent = malloc(sizeof(t_point*));
            ville->plateau[x][y]->parent->x = ville->coord_X;
            ville->plateau[x][y]->parent->y = ville->coord_Y;
            ville->plan_construction [x][y]=0;
        }
}

void charger_case(FILE*fp, t_ville* ville)
{
    int i,j;
    char c;
    fscanf(fp," %c", &c);
    if (c == '*')
    {
        fscanf(fp,"\n    CASE [%d][%d]",&i,&j);
        fscanf(fp,"        hapiness : %d\n",&(ville->plateau[i][j]->hapiness));
        fscanf(fp,"        densite : %d\n",&(ville->plateau[i][j]->densite));
        fscanf(fp,"        construction : %hd\n",&(ville->plateau[i][j]->construction));
        if (ville->plateau[i][j]->bat != NULL) charger_bat(fp,i,j, ville);
    }
}

void charger_plateau(FILE*fp, t_ville* ville)
{
    int i,j;

    for (i=0; i<LARGEUR_PLATEAU; i++)
    {
        for (j=0; j<HAUTEUR_PLATEAU; j++)
        {
            if (ville->plateau[i][j] != NULL) charger_case(fp, ville);
        }
    }
}

void charger_ville(FILE*fp, t_ville* ville)
{
    fscanf(fp,"population : %d\n",&(ville->population));
    fscanf(fp,"flouz : %d\n",&(ville->flouz));
    charger_plateau(fp, ville);
}

void charger_partie(t_ville* ville)
{
    FILE* fp=NULL;
    BITMAP *buffer_sauv=NULL;
    int i;
    init_ville(ville);

    char nom[56];   //les 5 lettres de .ece et le \0

    buffer_sauv=create_bitmap(SCREEN_LARGEUR,SCREEN_HAUTEUR);

    for (i=0; i<56; i++)
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
                ///effacer la dern�re lettre
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
        textprintf_centre_ex(buffer_sauv, font, SCREEN_W / 2, 120,makecol(0, 100, 243), -1,"ENTRER LE NOM DE LA SAUVEGARDE : %s.ece   50lettres maxi   ",nom);
        blit(buffer_sauv,screen, 0, 0, 0, 0,SCREEN_LARGEUR, SCREEN_HAUTEUR);
    }
    while (!key[KEY_ENTER] && strlen(nom)<50);

    ///ajout du .ece
    strcat(nom,".ece");
    fp=fopen(nom,"r");
    if (fp != NULL)// On peut lire et �crire dans le fichier
    {
        init_ville(ville);
        fscanf(fp,"Partie sauvegardee le ...\n");
        charger_ville(fp, ville);
    }
    else// On affiche un message d'erreur si on veut
    {
        printf("Erreur de lecture du fichier");
    }

    fclose(fp);
    update_route(ville);
}
