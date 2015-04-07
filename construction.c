#include "projet.h"

int test_constru=0;



t_case* creer_maison ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_MAISON_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_MAISON_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_MAISON_LV1;
    case_cree->bat->taille =1;
    case_cree->bat->image_bat = im_maison_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'm';
    case_cree->bat->rotation=0;
    return case_cree;
}

t_case* creer_commerce ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_COMMERCE_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_COMMERCE_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_COMMERCE_LV1;
    case_cree->bat->taille =1;
    case_cree->bat->image_bat = im_commerce_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'c';
    case_cree->bat->rotation=0;
    return case_cree;
}


t_case* creer_industrie ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=DENS_INDUSTRIE_CTR;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_INDUSTRIE_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_INDUSTRIE_LV1;
    case_cree->bat->taille =1;
    case_cree->bat->image_bat = im_industrie_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'i';
    case_cree->bat->rotation=0;
    return case_cree;
}


t_case* creer_centrale ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=0;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = CSMA_EAU_CENTRALE_LV1;
    case_cree->bat->consommation_elec = PRODU_ELEC_CENTRALE_LV1;
    case_cree->bat->taille =3;
    case_cree->bat->image_bat = centrale_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'e';
    case_cree->bat->rotation=0;
    return case_cree;
}



void init_construction (t_construction* construction)
{
    construction->case_a_construire=NULL;
    construction->construction=0;
    construction->creation_route=0;
}

int condition_placement (t_ville* ville, t_construction* construction)
{
    int espace = 1;
    int route = 0;
    int x,y;
    for (x=ville->coord_X ; x< ville->coord_X+construction->case_a_construire->bat->taille; x++)
        for (y=ville->coord_Y ; y< ville->coord_Y+construction->case_a_construire->bat->taille; y++)
        {
            if (!ville->plan_construction[x][y])
                espace = 0;
            if (ville->plan_construction[x][y] == 2)
                route = 1;
        }
    if (construction->case_a_construire->bat->type=='r' && ville->plan_construction[ville->coord_X][ville->coord_Y])
    {
        route=1;
        espace=1;
    }

    return route&&espace;
}

void placement (t_ville* ville, t_construction* construction)
{
    int condition = 0;
    int x,y;
    condition = condition_placement (ville, construction);

    if (!ville->plateau [ville->coord_X][ville->coord_Y]->construction && mouse_click && condition)
    {
        ville->plateau [ville->coord_X][ville->coord_Y]=construction->case_a_construire;
        ville->gestion_eau [ville->coord_X][ville->coord_Y] = construction->case_a_construire->bat->consommation_eau;
        ville->gestion_elec [ville->coord_X][ville->coord_Y] = construction->case_a_construire->bat->consommation_elec;
        for (x=ville->coord_X ; x<ville->coord_X+construction->case_a_construire->bat->taille ; x++)
            for (y=ville->coord_Y ; y<ville->coord_Y+construction->case_a_construire->bat->taille ; y++)
                ville->plan_construction [x][y]=0;


        construction->construction=0;
    }
}


void afficher_construction_en_cours (t_ville* ville, t_affichage* affichage_info, t_construction* construction, t_info_BFS* info)
{
    actualiser_coord (ville, affichage_info);

    if (construction->construction && construction->case_a_construire)
    {
        if (!ville->plateau [ville->coord_X][ville->coord_Y]->construction)
        {
            if (construction->case_a_construire->bat->type == 'r')
                affichage_construction_route (ville, construction, affichage_info, info);

            else if (construction->case_a_construire->bat->image_bat!=NULL)
                stretch_sprite(buffer, construction->case_a_construire->bat->image_bat, (TAILLE_CASE*ville->coord_X-affichage_info->depX)*affichage_info->zoom, (TAILLE_CASE*ville->coord_Y-affichage_info->depY)*affichage_info->zoom, construction->case_a_construire->bat->taille*TAILLE_CASE*affichage_info->zoom, construction->case_a_construire->bat->taille*TAILLE_CASE*affichage_info->zoom);
        }
    }
}

/*void placement_route (t_ville* ville, t_construction* construction)
{
    int i=0, j=0;
    int x,y, x_ini=0, y_ini=0, xi, yi;
    if (!construction->tab_route)
        construction->tab_route = malloc((LARGEUR_PLATEAU+HAUTEUR_PLATEAU)*sizeof (t_case*));

    if (construction->creation_route==1 && mouse_click)
    {
        for (i = 0 ; i<HAUTEUR_PLATEAU+LARGEUR_PLATEAU; i++)
        {
            construction->tab_route[i] = malloc (sizeof(t_route*));
            construction->tab_route[i]->raccord = 0;
            construction->tab_route[i]->coordx = 0;
            construction->tab_route[i]->coordy = 0;
            construction->tab_route[i]->image = NULL;
        }
        construction->tab_route[0]->coordx = ville->coord_X;
        construction->tab_route[0]->coordy = ville->coord_Y;
        //construction->tab_route[0]->raccord = detection_route (ville, ville->coord_X, ville->coord_Y);//a faire plus tard, pour l'affichage
        construction->creation_route=2;
        construction->tab_route[0]->image = im_route_1;
        printf ("X : %d\tY : %d\n", ville->coord_X, ville->coord_Y);
    }
    else if (construction->creation_route==2)
    {
        x = ville->coord_X;
        y = ville->coord_Y;
        x_ini = construction->tab_route[0]->coordx;
        y_ini = construction->tab_route[0]->coordy;
        for (i=1 ; i<LARGEUR_PLATEAU + HAUTEUR_PLATEAU ; i++)
            construction->tab_route[i]->image=NULL;

        ///printf ("x : %d\ty : %d\tx0 : %d\ty0 : %d\n", x, y ,x0, y0);

        if (x<x_ini)
            i=-1;
        else i=1;

        for (xi=0 ; xi < i*(x-x_ini) ; xi++)
        {
            construction->tab_route[xi]->coordx = x_ini + xi;
            construction->tab_route[xi]->coordy = y_ini;
            construction->tab_route[xi]->raccord = detection_route(ville, x_ini + i*xi, y_ini);
            attriubtion_image_route (construction, xi);
        }

        printf ("x = %d\t", i*xi);

        if (y<y_ini)
            j=-1;
        else j=1;

        for (yi=0 ; yi < j*(y-y_ini) ; yi++)
        {
            construction->tab_route[xi+yi]->coordx = x_ini + xi;
            construction->tab_route[xi+yi]->coordy = y_ini + yi;
            construction->tab_route[xi+yi]->raccord = detection_route(ville, x_ini + i*xi, y_ini + j*yi);
            attriubtion_image_route (construction, xi+yi);
        }
        printf("y = %d\n", j*yi);



        if (mouse_unclick)
            construction->creation_route=3;
    }
    else if (construction->creation_route==3)
    {
        if (x<x_ini)
            i=-1;
        else i=1;

            printf ("i : %d  x : %d  x_ini : %d\n", i, x, x_ini);

        for (xi=0 ; xi < i*(x-x0) ; xi++)
        {
            ville->plateau[x0 + i*xi][y0]->bat->image_bat = NULL;//construction->tab_route[xi]->image;
            ville->plateau[x0 + i*xi][y0]->construction=1;
            ville->plateau[x0 + i*xi][y0]->bat->type='r';
            printf ("xi : %d\t abs(x-x0) : \n", xi, i*(x-x0));
            //printf (" x :%d    y : % d\n",x0 + i*xi, y0);

        }

        if (y<y0)
            j=-1;
        else j=1;

        for (yi=0 ; yi < j*(y-y0) ; yi++)
        {
            ville->plateau[x0 + i*xi][y0+j*yi]->bat->image_bat = construction->tab_route[xi+yi]->image;
            ville->plateau[x0 + i*xi][y0+j*yi]->construction=1;
            ville->plateau[x0 + i*xi][y0+j*yi]->bat->type='r';
        }
        clean_construction_route (construction);
        construction->creation_route=0;
    }

}*/

void placement_route (t_ville* ville, t_info_BFS* info, t_construction* construction)
{
    if (mouse_click)
    {
        info->clique = 1;
        info->depart->x = ville->coord_X;
        info->depart->y = ville->coord_Y;
    }
    if (mouse_unclick && info->clique)
    {
        info->arrive->x = ville->coord_X;
        info->arrive->y = ville->coord_Y;
        printf ("\n%d %d   --  %d %d\n",info->depart->x, info->depart->y, info->arrive->x, info->arrive->y);
        algorithme (ville, info);
        info->depart->x = 0;
        info->depart->y = 0;
        info->arrive->x = 0;
        info->arrive->y = 0;
        info->clique=0;
        construction->creation_route=0;
        construction->construction=0;
            }
}

int detection_route (t_ville* ville, int x, int y)
{
    int raccord=0;
    if (x>0 && ville->plateau[x-1][y]->bat->type=='r')
        raccord = 100;
    if (x< LARGEUR_PLATEAU-1 && ville->plateau[x+1][y]->bat->type=='r')
        raccord = raccord + 1;
    if (y>0 &&  ville->plateau[x][y-1]->bat->type=='r')
        raccord = raccord +1000;
    if (y< HAUTEUR_PLATEAU-1 && ville->plateau[x][y+1]->bat->type=='r')
        raccord = raccord + 10;
    printf("%d   ", raccord);
    return raccord;
}

void attriubtion_image_route (t_case* tcase, int raccord)
{
    ///printf ("%d\n",raccord);
    switch (raccord)
    {
    case 0 :
        tcase->bat->image_bat = im_route_1;
        tcase->bat->rotation=192;
        break;
    case 1 :
        tcase->bat->image_bat = im_route_1;
        tcase->bat->rotation=128;
        break;
    case 10 :
        tcase->bat->image_bat = im_route_1;
        tcase->bat->rotation=192;
        break;
    case 100 :
        tcase->bat->image_bat = im_route_1;
        tcase->bat->rotation=0;
        break;
    case 1000 :
        tcase->bat->image_bat = im_route_1;
        tcase->bat->rotation=64;
        break;
    case 11 :
        tcase->bat->image_bat = im_route_2;
        tcase->bat->rotation=192;
        break;
    case 110 :
        tcase->bat->image_bat = im_route_2;
        tcase->bat->rotation=0;
        break;
    case 1100 :
        tcase->bat->image_bat = im_route_2;
        tcase->bat->rotation=64;
        break;
    case 1010 :
        tcase->bat->image_bat = im_route_d;
        tcase->bat->rotation=64;
        break;
    case 1001 :
        tcase->bat->image_bat = im_route_2;
        tcase->bat->rotation=128;
        break;
    case 101 :
        tcase->bat->image_bat = im_route_d;
        tcase->bat->rotation=0;
        break;
    case 111 :
        tcase->bat->image_bat = im_route_3;
        tcase->bat->rotation=128;
        break;
    case 1110 :
        tcase->bat->image_bat = im_route_3;
        tcase->bat->rotation=192;
        break;
    case 1101 :
        tcase->bat->image_bat = im_route_3;
        tcase->bat->rotation=0;
        break;
    case 1011 :
        tcase->bat->image_bat = im_route_3;
        tcase->bat->rotation=64;
        break;
    case 1111 :
        tcase->bat->image_bat = im_route_4;
        tcase->bat->rotation=0;
        break;
    }
}
