#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "../MODULE_TABLE/table.h"

typedef struct kdtree * kdtree;
/**
 * @brief       Permet de choisir un axe avec les plus grandes projections
 * @details    	Somme tous les composantes d une couleur donne et les compare
 * @param    	table  	Une table de couleur en entrée

 * @return   	axis 	L axe avec les plus grandes projections
 */
int getAxisMax(color_table table);


/**
 * @brief    Affiche le kd arbre
 * @param    kdtree 	Prend en parametre un kd arbre
 */
void afficher_kdtree(kdtree kdt);



kdtree create_kdtree(color_table,int);

void destroy_kdtree(kdtree);

void kdtree_get_nearest_color(kdtree kdt, color * c, color * output);


#endif
