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
    case_cree->bat->taille_x = 3;
    case_cree->bat->taille_y = 3;
    case_cree->bat->image_bat = im_maison_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'm';
    case_cree->bat->rotation=0;
    case_cree->parent=malloc(sizeof(t_point*));
    case_cree->age=0;
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
    case_cree->bat->taille_x = 3;
    case_cree->bat->taille_y = 3;
    case_cree->bat->image_bat = im_commerce_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'c';
    case_cree->bat->rotation=0;
    case_cree->parent=malloc(sizeof(t_point*));
    case_cree->age=0;
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
    case_cree->bat->taille_x = 3;
    case_cree->bat->taille_y = 3;
    case_cree->bat->image_bat = im_industrie_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'i';
    case_cree->bat->rotation=0;
    case_cree->parent=malloc(sizeof(t_point*));
    case_cree->age=0;
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
    case_cree->bat->taille_x = 4;
    case_cree->bat->taille_y = 6;
    case_cree->bat->image_bat = im_centrale_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'e';
    case_cree->bat->rotation=0;
    case_cree->parent=malloc(sizeof(t_point*));
    case_cree->appro_elec = PRODU_ELEC_CENTRALE_LV1;
    case_cree->age=0;
    return case_cree;
}


t_case* creer_chateau ()
{
    t_case* case_cree;
    case_cree = malloc (sizeof (t_case));
    case_cree->construction=1;
    case_cree->densite=0;
    case_cree->hapiness=0;
    case_cree->bat = malloc(sizeof (t_bat));
    case_cree->bat->consommation_eau = PRODU_EAU_CHATEAU_LV1;
    case_cree->bat->consommation_elec = CSMA_ELEC_CHATEAU_LV1;
    case_cree->bat->taille_x = 4;
    case_cree->bat->taille_y = 6;
    case_cree->bat->image_bat = im_chateau_lv1;
    //case_cree->bat->image_bat = NULL;
    case_cree->bat->type = 'o';
    case_cree->bat->rotation=0;
    case_cree->appro_eau = PRODU_EAU_CHATEAU_LV1;
    case_cree->parent=malloc(sizeof(t_point*));
    case_cree->age=0;
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
    for (x=ville->coord_X ; x< ville->coord_X+construction->case_a_construire->bat->taille_x; x++)
        for (y=ville->coord_Y ; y< ville->coord_Y+construction->case_a_construire->bat->taille_y; y++)
        {
            if (ville->coord_X+construction->case_a_construire->bat->taille_x>LARGEUR_PLATEAU || ville->coord_Y+construction->case_a_construire->bat->taille_y > HAUTEUR_PLATEAU)
                espace = 0;
            else
            {
                if (!ville->plan_construction[x][y])
                    espace = 0;
                if (ville->plan_construction[x][y] == 2)
                    route = 1;
            }
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
        for (x=ville->coord_X ; x<ville->coord_X+construction->case_a_construire->bat->taille_x ; x++)
            for (y=ville->coord_Y ; y<ville->coord_Y+construction->case_a_construire->bat->taille_y ; y++)
            {
                if (!ville->plateau[x][y]->parent)
                    ville->plateau[x][y]->parent = malloc(sizeof(t_point*));
                ville->plateau[x][y]->parent->x = ville->coord_X;
                ville->plateau[x][y]->parent->y = ville->coord_Y;
                ///printf ("Parent : %d %d\n",  ville->plateau[x][y]->parent->x,  ville->plateau[x][y]->parent->y );
                ville->plan_construction [x][y]=0;
                ville->plateau[x][y]->construction=1;
            }


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
                stretch_sprite(buffer, construction->case_a_construire->bat->image_bat, (TAILLE_CASE*ville->coord_X-affichage_info->depX)*affichage_info->zoom, (TAILLE_CASE*ville->coord_Y-affichage_info->depY)*affichage_info->zoom, construction->case_a_construire->bat->taille_x*TAILLE_CASE*affichage_info->zoom, construction->case_a_construire->bat->taille_y*TAILLE_CASE*affichage_info->zoom);
        }
    }
}


void placement_route (t_ville* ville, t_info_BFS* info, t_construction* construction)
{
    int sortie;
    if (mouse_click && ville->plan_construction[ville->coord_X][ville->coord_Y])
    {
        info->clique = 1;
        info->depart[0] = malloc(sizeof(t_point*));
        info->depart[0]->x = ville->coord_X;
        info->depart[0]->y = ville->coord_Y;
    }
    if (mouse_unclick && info->clique)
    {
        info->arrive->x = ville->coord_X;
        info->arrive->y = ville->coord_Y;
        printf ("\n%d %d   --  %d %d\n",info->depart[0]->x, info->depart[0]->y, info->arrive->x, info->arrive->y);
        sortie = algorithme (ville, info);
        tracage_route(ville, info, sortie);
        reset_info (info, ville);
        reset_marqueur (ville);
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
