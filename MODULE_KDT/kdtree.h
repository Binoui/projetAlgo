#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "../MODULE_TABLE/table.h"

typedef struct kdtree * kdtree;
/**
 * @brief       Permet de choisir un axe avec les plus grandes projections
 * @details    	Somme tous les composantes d une couleur donne et les compare
 * @param    	table  	Une table de couleur en entrée de type color_table
 * @return   	axis 	L axe avec les plus grandes projections
 */
int getAxisMax(color_table table);


/**
 * @brief    Affiche le kd arbre
 * @param    kdtree 	Prend en parametre un kd arbre
 */
void afficher_kdtree(kdtree kdt);


/**
 * @brief 	Crée un kd-arbre
 * @details 	Permet à partir d'une table et d'un entier de créer un kd arbre complet
 * @param	color_table Une table de couleur en entrée
 * @param 	limit Un entier correspondant à la limite du nombre d'élément pour le sous arbre
 * @return 	kdtree Renvoie le kd-arbre complet
*/
kdtree create_kdtree(color_table,int);

/**
* @brief 	Désalloue le kd-arbre
* @details 	La désallocation se fait de manière récursive
* @param	kdtree Un kd-arbre en paramètre
*/
void destroy_kdtree(kdtree);


/**
* @brief	Permet de récuperer la couleur la plus proche dans le kd-arbre 
* @details 	On va chercher la couleur dans une feuille, ensuite on vérifie si la sphère avec pour centre le point cherché et de rayon la distance point charché-point trouvé intersecte le plan de coupe.Si c'est le cas on fait une recherche dans l'autre fils du noeud lors de la remontée
* @param 	kdt Un kd-arbre en entrée
* @param	c La couleur à chercher de type color
* @param	output La couleur trouvée de type color
*/
void kdtree_get_nearest_color(kdtree kdt, color * c, color * output);


#endif
