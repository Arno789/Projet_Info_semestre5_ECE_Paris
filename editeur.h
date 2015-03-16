#ifndef EDITEUR_H_INCLUDED
#define EDITEUR_H_INCLUDED
#define LARGEUR_PLATEAU 45
#define HAUTEUR_PLATEAU 35

#define DENS_MAISON_CTR 0
#define CSMA_EAU_MAISON_LV1 0
#define CSMA_ELEC_MAISON_LV1 0

#define DENS_COMMERCE_CTR 0
#define CSMA_EAU_COMMERCE_LV1 0
#define CSMA_ELEC_COMMERCE_LV1 0

#define DENS_INDUSTRIE_CTR 0
#define CSMA_EAU_INDUSTRIE_LV1 0
#define CSMA_ELEC_INDUSTRIE_LV1 0


extern char touche;  ///Déclaration type compalleg *///
                                                    ///
extern char bouton;                                 ///
                                                    ///
extern int mouse_click;                             ///
                                                    ///
                                                    ///
extern int mouse_unclick;                           ///
                                                    ///
                                                    ///
extern int key_press[KEY_MAX];                      ///
extern int key_unpress[KEY_MAX];                    ///
                                                    ///
                                                    ///
extern int mouse_depx;                              ///
extern int mouse_depy;                              ///

extern int coord_X, coord_Y;  ///Variable globale indiquant les coordonnées de la case 'active'

void rafraichir_clavier_souris();
extern int test_constru;


#endif // EDITEUR_H_INCLUDED
