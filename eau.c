#include "projet.h"

///La capacit� totale d�un ch�teau d�eau permet d�alimenter en permanence 5000 habitants.


void update_eau (t_ville* ville, t_info_BFS* info)
{
    int x,y,i,j,k, parent_x, parent_y;
    i=0;
    j=0;
    reset_info_eau(info, ville);
    reset_marqueur (ville);

/// On reinitialise toutes les valeur d'approvisionnement a 0
/// Sauf pour les chateaux d'eau qui b�n�ficient d'untraitement sp�cial

    for (i=0 ; i<LARGEUR_PLATEAU ; i++)
        for (j=0 ; j<HAUTEUR_PLATEAU ; j++)
            if ((ville->plateau[i][j]->bat->type=='m' || ville->plateau[i][j]->bat->type=='c' || ville->plateau[i][j]->bat->type=='i'))
                ville->plateau[i][j]->appro_eau=0;
            else if (ville->plateau[i][j]->bat->type=='o')
                ville->plateau[i][j]->appro_eau = ville->plateau[i][j]->bat->consommation_eau;

///On va scanner tout le plateau a la recherche de chateaux d'eau
    for (x=0 ; x<LARGEUR_PLATEAU ; x++)
    {
        for (y=0 ; y<HAUTEUR_PLATEAU ; y++)
        {
            if (ville->plateau[x][y]->construction && ville->plateau[x][y]->parent) ///Si on a trouv� une construction quelconque qui a une case parent
                ///donc a priori un construction de taille min 3x3
            {
                /// On enregistre les coordonn�es de la case parente pour simplifier les expressions
                parent_x = ville->plateau[x][y]->parent->x;
                parent_y = ville->plateau[x][y]->parent->y;

                if (ville->plateau[parent_x][parent_y]->bat) ///Simple if de s�curit�, normalement toujours v�rifi�
                    if (ville->plateau[parent_x][parent_y]->bat->type == 'o' && !ville->plateau[parent_x][parent_y]->marqueur)
                        ///Si la case scann�e est un chateau d'eau et qu'il n'a pas d�j� �t� scann� avant
                    {
                        k=0; ///initialisation des points de d�part de l'algo
                        for (i=0 ; i<ville->plateau[parent_x][parent_y]->bat->taille_x ; i++)
                        {
                            for (j=0 ; j<ville->plateau[parent_x][parent_y]->bat->taille_y ; j++)
                            {
                                if (!i || !j || i==ville->plateau[parent_x][parent_y]->bat->taille_x-1 || j==ville->plateau[parent_x][parent_y]->bat->taille_y-1)
                                ///on ne r�cup�re toutes les cases en p�rif�rie du chateau d'eau (donc 5+3+5+3)
                                {
                                    ///On alloue, pour un plus grande optimisation m�moire , on free tout ce que n'est pas utile
                                    if (!info->depart[k])
                                        info->depart[k] = malloc(sizeof(t_point*));
                                    ///On enregistre les coordonn�es dans le tableau pr�vu a cet effet
                                    info->depart[k]->x = parent_x + i;
                                    info->depart[k]->y = parent_y + j;
                                    k++;
                                }
                                /// On marque les cases du chateaux pour ne pas les re s�lectionner par la suite
                                ville->plateau[parent_x + i][parent_y + j]->marqueur=1;
                            }
                        }
                        /// Apres qu'on est trouv� un chateau et effectu� tous les traitement pour le pr�parer,
                        /// On lance l'algorithme
                        algorithme_eau(ville, info, ville->plateau[parent_x][parent_y]->bat->consommation_eau);

                        reset_info_eau(info, ville);
                        ///On ne reset que les marqueurs sur les routes, pas sur les batiements
                        reset_marqueur_route (ville);
                        //printf("algo eau\n");
                    }

            }
        }
    }
    /// va checker toutes les cases du terrain pour v�rifier si elles sont approvisionn�es
    verification_distrib_eau (ville);
}


void algorithme_eau (t_ville* ville, t_info_BFS* info, int capa_totale)
{
    ///Capa_totale est le nombre d'habitant max que la somme des chateaux d'eau peut fournir
    t_point* tab [100];
    t_point* tab2 [100];

    ///En gros :
    ///tab contient les points analys� au tour de boucle pr�c�dent, tous les calculs s'effecturont uniquement sur ces points
    ///tab2 contient les r�ultat des points qui viennetn d'�tre analys�

    int sortie=0;
    int i=0, j;
    int x, y, a, b;
    int parent_x, parent_y;

    init_tab (tab);   ///On s'assure que tout est bien pr�t avant de lancer l'algorithme
    init_tab (tab2);    ///


///On met � jour la matrice d'ajacence
    //update_adjacence (ville);

    while (info->depart[i])   ///Va contenir toutes les cases des chateaus d'eau reli�es � une route
    {
        tab[i] = malloc(sizeof(t_point*));
        tab[i]->x = info->depart[i]->x; /// Le premier point qui vat �tre analys� est le point de d�part
        tab[i]->y = info->depart[i]->y; ///
        i++;
    }


    while (!sortie)
    {
        i=0; ///Re initialisation des variables
        j=0;

        while (tab[i]!=NULL && !sortie)
        {
            //printf ("i : %d\n", i);
            ///Les quatre grand 'if' suivant sont l'analyse des points directement voisins (gauche, droite, haut, bas) du point en cours d'analyse
            /// Le point en cors d'analyse est s�lectionn� dans 'tab', les r�ultats de ces analyses sont eux stock� dans tab2
            /// ici les 4 if vont servir a d�terminer le chemin que l'algo devra suivre, ils d�tectent les routes voisine non parcourues et les enregistres pour qu'elles soient traitees au prochai tour de boucle
            if (tab[i]->x-1>0)
                if (ville->plateau[tab[i]->x-1][tab[i]->y]->bat->type=='r' && ville->plateau[tab[i]->x-1][tab[i]->y]->marqueur == 0) //Si c'est une route par laquelle on n'est jamais pass�
                {
                    info->l[tab[i]->x-1][tab[i]->y] = info->l[tab[i]->x][tab[i]->y] + 1; ///La distance entre chaque case voisine est de une unit�
                    ville->plateau[tab[i]->x-1][tab[i]->y]->marqueur = 1; ///on marque la case qu'on vient d'analyser
                    info->pred[tab[i]->x-1][tab[i]->y]->x = tab[i]->x; ///On enregistre les coordonn�es du pr�decesseur de cette case
                    info->pred[tab[i]->x-1][tab[i]->y]->y = tab[i]->y;
                    tab2[j]=malloc(sizeof(t_point*)); ///On inscrit la case scann�e dans le 'tab2' pour que cette case permette de scanner de nouvelles cases a partir d'elle
                    tab2[j]->x = tab[i]->x-1;
                    tab2[j]->y = tab[i]->y;
                    j++;
                }

            if (tab[i]->y-1>0)
            {
                if (ville->plateau[tab[i]->x][tab[i]->y-1]->bat->type=='r' && ville->plateau[tab[i]->x][tab[i]->y-1]->marqueur == 0) //Si c'est une route par laquelle on n'est jamais pass�
                {
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
                if (ville->plateau[tab[i]->x+1][tab[i]->y]->bat->type=='r' && ville->plateau[tab[i]->x+1][tab[i]->y]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
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
                if (ville->plateau[tab[i]->x][tab[i]->y+1]->bat->type=='r' && ville->plateau[tab[i]->x][tab[i]->y+1]->marqueur == 0) //Si un liaison est possible, -> s'il n'y a pas de construction
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
            for (a=-1 ; a<1 ; a++) ///on test les cases � gauche, droite, au dessus et en dessous
            {
                if (!a)
                    a++;
                for (b=-1 ; b<1 ; b++)
                {
                    if (!b)
                        b++;

                    if (ville->plateau[tab[i]->x+a][tab[i]->y+b]->construction &&  ville->plateau[tab[i]->x+a][tab[i]->y+b]->parent && !ville->plateau[tab[i]->x+a][tab[i]->y+b]->marqueur)    /// S'il y a quelque chose sur cette case
                    {
                        parent_x = ville->plateau[tab[i]->x+a][tab[i]->y+b]->parent->x;  /// On se r�f�re a son parent,
                        parent_y = ville->plateau[tab[i]->x+a][tab[i]->y+b]->parent->y;
                        if ((ville->plateau[parent_x][parent_y]->bat->type == 'm' || ville->plateau[parent_x][parent_y]->bat->type == 'c' || ville->plateau[parent_x][parent_y]->bat->type == 'i') && ville->plateau[parent_x][parent_y]->bat->consommation_eau != ville->plateau[parent_x][parent_y]->appro_eau)
                        /// Si cette case n'a pas �t�e completement apprivisionn�e et si elle est approvisionnable

                        {
                            if (capa_totale >=  ville->plateau[parent_x][parent_y]->bat->consommation_eau)  ///S'il reste suffisamment d'eau pour allimenter tout le bat
                            {
                                /// Mise � jour de la capacit� restante du chateau d'eau
                                capa_totale = capa_totale - ville->plateau[parent_x][parent_y]->bat->consommation_eau;
                                ville->plateau[parent_x][parent_y]->appro_eau =  ville->plateau[parent_x][parent_y]->bat->consommation_eau;
                            }
                            else    ///Sinon
                            {
                                ville->plateau[parent_x][parent_y]->appro_eau = capa_totale;
                                capa_totale = 0;
                            }

                        }
                    }
                }
            }
            /// S'il n'y a plus d'eau das le chateau
            if (!capa_totale)
            {
                sortie = 1;
                //printf ("Il n'y a pas assez de chateau d'eau !\n");
            }

            i++; ///On passe a la case suivante de 'tab'
        }


        /// On effectue le transfert de tableau : on copie les points du 'tab2' dans 'tab' pour qu'on puisse analyser les voisins de ces points l�
        for (i=0 ; i<j ; i++)
        {
            if (!tab[i])
                tab[i] = malloc(sizeof(t_point*)); ///Il y a de fortes chances que le nombre de r�sultats dans 'tab2' soit plus grand que celui dans 'tab' il faut donc allouer de nouveaux point au tableau

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
        if (!tab2[0]) ///Ou on finit quand il n'y a plus de nouvelle case a scanner
        {
            sortie=2;
            //printf ("Approvisionnement termine !\n");
        }

        init_tab(tab2);
    }
}


void reset_info_eau (t_info_BFS* info, t_ville* ville)
{
    int i;
    info->arrive->x=0;
    info->arrive->y=0;
    info->clique = 0;

    for (i=0 ; i< 30 ; i++)
    {
        if (info->depart[i])
            free (info->depart[i]);
        info->depart[i] = NULL;
    }
}

void reset_marqueur_route (t_ville* ville)
{
    int i,j;
    for (i=0 ; i<LARGEUR_PLATEAU ; i++)
    {
        for (j=0 ; j<HAUTEUR_PLATEAU ; j++)
        {
            if (ville->plateau[i][j]->bat && ville->plateau[i][j]->bat->type == 'r')
                ville->plateau[i][j]->marqueur=0;
        }
    }
}

void verification_distrib_eau (t_ville* ville)
{
    int i,j, cool;
    cool = 1; ///Faut toujours �tre positif
    for (i=0 ; i<LARGEUR_PLATEAU ; i++)
    {
        for (j=0 ; j<HAUTEUR_PLATEAU ; j++)
        {
            if (ville->plateau[i][j]->bat && ville->plateau[i][j]->bat->consommation_eau != ville->plateau[i][j]->appro_eau && (ville->plateau[i][j]->bat->type=='m' || ville->plateau[i][j]->bat->type=='c' || ville->plateau[i][j]->bat->type=='i'))
                cool =0;
        }
    }
    if (cool)
        printf ("Tout le monde a de l'eau !\n");
    else printf ("Leger soucis d'eau\n");
}
