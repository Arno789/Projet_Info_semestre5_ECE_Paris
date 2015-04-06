#include "projet.h"

t_case* creer_route ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=0;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = 0;
    case_cree->bat->consommation_elec = 0;
    case_cree->bat->image_bat = im_route_n;
    case_cree->bat->type = 'r';
    case_cree->bat->taille=1;
    return case_cree;
}

void affichage_construction_route (t_ville* ville, t_construction* construction, t_affichage* affichage_info, t_info_BFS* info)
{
    int x1, y1, x2, y2;
    if (info->clique)
    {

        x1 = info->depart->x*TAILLE_CASE*affichage_info->zoom-affichage_info->depX+5;
        y1 = info->depart->y*TAILLE_CASE*affichage_info->zoom-affichage_info->depY+5;
        if (x1<0)
            x1=0;
        if (x1>SCREEN_W)
            x1 = SCREEN_W;
        if (y1<0)
            y1=0;
        if (y1>SCREEN_H)
            y1 = SCREEN_H;

        x2 = mouse_x;
        y2 = mouse_y;

        line (buffer, x1, y1, x2, y2, makecol(255,0,0));
    }

}


void algorithme (t_ville* ville, t_info_BFS* info) ///Attention ca pique les yeux
{
    t_point* tab [100];
    t_point* tab2 [100];

    ///En gros :
    ///tab contient les points analysé au tour de boucle précédent, tous les calculs s'effecturont uniquement sur ces points
    ///tab2 contient les réultat des points qui viennetn d'être analysé

    int sortie=0;
    int i, j;
    int x, y;
    int compteur_secu = 0;

    init_tab (tab);   ///On s'assure que tout est bien prèt avant de lancer l'algorithme
    init_tab (tab2);    ///
    reset_info (info, ville);///

///On met à jour la matrice d'ajacence
    //update_adjacence (ville);


    tab[0] = malloc(sizeof(t_point*));
    tab[0]->x = info->depart->x; /// Le premier point qui vat être analysé est le point de départ
    tab[0]->y = info->depart->y; ///

    while (!sortie)
    {
        compteur_secu++; ///Si apres avoir fait toutes les possibilité la rechercher n'a rien donné ...
        if (compteur_secu > LARGEUR_PLATEAU * HAUTEUR_PLATEAU)
        {
            allegro_message(" Aucun chemin n'a put etre trouve !");
            sortie = 666; ///SATAN
        }

        i=0; ///Re initialisation des variables
        j=0;
        while (tab[i]!=NULL)
        {
            ///Les quatre grand 'if' suivant sont l'analyse des points directement voisins (gauche, droite, haut, bas) du point en cours d'analyse
            /// Le point en cors d'analyse est sélectionné dans 'tab', les réultats de ces analyses sont eux stocké dans tab2
            if (tab[i]->x-1>0)
                if ((ville->plan_construction[tab[i]->x-1][tab[i]->y] || ville->plateau[tab[i]->x-1][tab[i]->y]->bat->type=='r') && ville->plateau[tab[i]->x-1][tab[i]->y]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
                {
                    ///Si on repasse par dessus une route, devons nous compter le surplus de case (si on passe sur une route, on ne créé pas de route en plus de celle existante, pourtant la distance évolue quand même)
                    //if (ville->plan_construction[tab[i]->x-1][tab[i]->y]==1)
                    info->l[tab[i]->x-1][tab[i]->y] = info->l[tab[i]->x][tab[i]->y] + 1; ///La distance entre chaque case voisine est de une unité
                    ville->plateau[tab[i]->x-1][tab[i]->y]->marqueur = 1; ///on marque la case qu'on vient d'analyser
                    info->pred[tab[i]->x-1][tab[i]->y]->x = tab[i]->x; ///On enregistre les coordonnées du prédecesseur de cette case
                    info->pred[tab[i]->x-1][tab[i]->y]->y = tab[i]->y;
                    tab2[j]=malloc(sizeof(t_point*)); ///On inscrit la case scannée dans le 'tab2' pour que cette case permette de scanner de nouvelles cases a partir d'elle
                    tab2[j]->x = tab[i]->x-1;
                    tab2[j]->y = tab[i]->y;
                    j++;
                }

            if (tab[i]->y-1>0)
            {
                if ((ville->plan_construction[tab[i]->x][tab[i]->y-1] || ville->plateau[tab[i]->x][tab[i]->y-1]->bat->type=='r') && ville->plateau[tab[i]->x][tab[i]->y-1]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
                {
                    //if (ville->plan_construction[tab[i]->x][tab[i]->y-1]==1)
                    info->l[tab[i]->x][tab[i]->y-1] = info->l[tab[i]->x][tab[i]->y] + 1;
                    ville->plateau[tab[i]->x][tab[i]->y-1]->marqueur = 1;
                    info->pred[tab[i]->x][tab[i]->y-1]->x = tab[i]->x;
                    info->pred[tab[i]->x][tab[i]->y-1]->y = tab[i]->y;
                    tab2[j]=malloc(sizeof(t_point*));
                    tab2[j]->x = tab[i]->x;
                    tab2[j]->y = tab[i]->y-1;
                    j++;
                }
            }

            if (tab[i]->x+1<LARGEUR_PLATEAU)
            {
                if ((ville->plan_construction[tab[i]->x+1][tab[i]->y] || ville->plateau[tab[i]->x+1][tab[i]->y]->bat->type=='r') && ville->plateau[tab[i]->x+1][tab[i]->y]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
                {
                    //if (ville->plan_construction[tab[i]->x+1][tab[i]->y]==1)
                    info->l[tab[i]->x+1][tab[i]->y] = info->l[tab[i]->x][tab[i]->y] + 1;
                    ville->plateau[tab[i]->x+1][tab[i]->y]->marqueur = 1;
                    info->pred[tab[i]->x+1][tab[i]->y]->x = tab[i]->x;
                    info->pred[tab[i]->x+1][tab[i]->y]->y = tab[i]->y;
                    tab2[j]=malloc(sizeof(t_point*));
                    tab2[j]->x = tab[i]->x+1;
                    tab2[j]->y = tab[i]->y;
                    j++;
                }
            }

            if (tab[i]->y+1<HAUTEUR_PLATEAU)
            {
                if ((ville->plan_construction[tab[i]->x][tab[i]->y+1] || ville->plateau[tab[i]->x][tab[i]->y+1]->bat->type=='r')&& ville->plateau[tab[i]->x][tab[i]->y+1]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
                {
                    //if (ville->plan_construction[tab[i]->x][tab[i]->y+1]==1)
                    info->l[tab[i]->x][tab[i]->y+1] = info->l[tab[i]->x][tab[i]->y] + 1;
                    ville->plateau[tab[i]->x][tab[i]->y+1]->marqueur = 1;
                    info->pred[tab[i]->x][tab[i]->y+1]->x = tab[i]->x;
                    info->pred[tab[i]->x][tab[i]->y+1]->y = tab[i]->y;
                    tab2[j]=malloc(sizeof(t_point*));
                    tab2[j]->x = tab[i]->x;
                    tab2[j]->y = tab[i]->y+1;
                    j++;
                }
            }

            if (tab[i]->x == info->arrive->x && tab[i]->y == info->arrive->y)
                sortie = 1; ///On a fini que quand l'algo tombe (par hasard, apres avoir épuisé un certain nombre de possibilités) sur la case d'arrivée

            i++; ///On passe a la case suivante de 'tab'
        }
        printf("\n%d  ", j); /// On affiche le nombre de case ayant correspondu aux attentes du scan (donc de 0 compris à 4 compris)

        /// On effectue le transfert de tableau : on copie les points du 'tab2' dans 'tab' pour qu'on puisse analyser les voisins de ces points là
        for (i=0 ; i<j ; i++)
        {
            if (!tab[i])
                tab[i] = malloc(sizeof(t_point*)); ///Il y a de fortes chances que le nombre de résultats dans 'tab2' soit plus grand que celui dans 'tab' il faut donc allouer de nouveaux point au tableau

            x = tab2[i]->x;
            y = tab2[i]->y;

            tab [i]->x = x;
            tab [i]->y = y;
        }
        while (i<99)  ///On complete la fin du tableau par des pointeurs sur NULL
        {
            i++;
            tab[i]=NULL;
        }
        init_tab(tab2);
    }

    if (sortie != 666) ///Si l'algorithme a reussi a trouver un chemin :
    {
        printf("\nDistance minimum : %d\n", info->l[info->arrive->x][info->arrive->y]);

        x=info->arrive->x;
        y=info->arrive->y;
        sortie =0;
        ville->plateau[x][y]->construction=2;
        ville->plateau[x][y]->bat->type = 'r';
        ville->plan_construction[x][y] = 0;
        while (!sortie)
        {
///On va refaire le chemin inverse en parcourant le tabelau 'perd' qui contient les coordonnées de la case mère de chaque case, jusqu'à ce qu'on revienne à la case de départ
            if (x != info->depart->x || y!=info->depart->y)
            {
                i = info->pred[x][y]->x;
                j = info->pred[x][y]->y;
                x = i;
                y = j;
            }
            ville->plateau[x][y]->construction=2;
            ville->plateau[x][y]->bat->type = 'r';
            ville->plan_construction[x][y] = 0;
            printf("*"); ///Affichage d'une étoile pour chaque route créée (oui, ceci ne sert à rien , c'est juste joli)
            if (x==info->depart->x && y==info->depart->y) ///Tant qu'on n'est pas revenu à notre point de départ, on reste dans la boucle
                sortie=1;
            else sortie=0;
        }
        printf ("\n");
    }

    for (x=0 ; x<LARGEUR_PLATEAU ; x++)
    {
        for (y=0 ; y<HAUTEUR_PLATEAU ; y++)
        {
            if (ville->plateau[x][y]->construction==2)
            {
                i = detection_route (ville, x, y);
                attriubtion_image_route (ville->plateau[x][y], i);
                ville->plateau[x][y]->bat->taille=1;

                printf("%d  %p\n", ville->plateau[x][y]->bat->rotation, ville->plateau[x][y]->bat->image_bat);

                if (x>0 && ville->plan_construction [x-1][y]!=0)
                    ville->plan_construction [x-1][y]=2;

                if (x+1<LARGEUR_PLATEAU && ville->plan_construction [x+1][y]!=0)
                    ville->plan_construction [x+1][y]=2;

                if (y>0 && ville->plan_construction [x][y-1]!=0)
                    ville->plan_construction [x][y-1]=2;

                if (y+1<HAUTEUR_PLATEAU && ville->plan_construction [x][y+1]!=0)
                    ville->plan_construction [x][y+1]=2;
            }
        }
    }
    ///FIN DE L' ALGO
}


void init_info (t_info_BFS* info)
{
    int i, j;
    info->depart=malloc(sizeof(t_point*));
    info->depart->x=0;
    info->depart->y=0;
    info->arrive=malloc(sizeof(t_point*));
    info->arrive->x=0;
    info->arrive->y=0;
    info->clique = 0;

    info->l = malloc(LARGEUR_PLATEAU*sizeof(int*));
    info->pred= malloc(LARGEUR_PLATEAU*sizeof(t_point***));

    for (i=0 ; i<LARGEUR_PLATEAU ; i++)
    {
        info->l[i] =   malloc(HAUTEUR_PLATEAU*sizeof(int));
        info->pred[i] =   malloc(HAUTEUR_PLATEAU*sizeof(t_point**));
        for (j=0 ; j<HAUTEUR_PLATEAU ; j++)
        {
            info->l[i][j]=0;
            info->pred[i][j] = malloc(sizeof(t_point*));
        }
    }
}

void reset_info (t_info_BFS* info, t_ville* ville)
{
    int i,j;
    for (i=0 ; i<LARGEUR_PLATEAU ; i++)
    {
        for (j=0 ; j<HAUTEUR_PLATEAU ; j++)
        {
            info->pred [i][j]->x = 0;
            info->pred [i][j]->y = 0;
            info->l[i][j]=0;
            ville->plateau[i][j]->marqueur=0;
        }
    }
}

void init_tab (t_point* tab [100])
{
    int i;
    for (i=0 ; i<100 ; i++)
    {
        tab[i]=NULL;
    }
}
