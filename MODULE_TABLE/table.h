#ifndef __TABLE_HH__
#define __TABLE_HH__

#include "../MODULE_IMAGE/image.h"

/* Différentes composantes couleurs */
typedef enum {	red,
		green,
		blue
}axis;

typedef unsigned char color; /* UNSIGNED CHAR PLUTOT QUE CHAR OU INT */
typedef enum {false,true} boolean;

typedef struct color_table * color_table;

typedef int (*FCT_CMP)(const void *, const void *);

/**
* @brief Crée une table de couleur à partir d'une image
* @param img Image a prendre pour créer la table de couleur
* @return color_table Retourne la table de couleur
*/
color_table create_color_table(image);

/**
* @brief Librère la table de couleur, et le tableau si  
* @param img Image a prendre pour créer la table de couleur
* @return color_table Retourne la table de couleur
*/
boolean destroy_color_table(color_table);

/**
* @brief Crée une sous table à partir d'une table de couleur 
* @param color_table Une table de couleur en entrée
* @param offset Index de départ de la sous table
* @param length Correspond à la longueur de la sous table
* @return color_table Renvoie une sous table de couleur
*/ 

color_table color_table_duplicate(color_table,int,int);

/**
* @brief Crée une sous table à partir d'une table de couleur 
* @param color_table Une table de couleur en entrée
* @param offset Index de départ de la sous table
* @param length Correspond à la longueur de la sous table
* @return color_table Renvoie une sous table de couleur
*/ 
void color_table_get_color(color_table,int,color*);

/**
* @brief Donne le nombre de couleurs d'une table
* @param color_table Une table de couleur en entrée
* @return nombre de couleurs de la table
*/ 
int color_table_get_nb_color(color_table);

/**
* @brief Trie la table de couleur en fonction d'une couleur
* @param color_table Une table de couleur à trier en entrée
* @param axis Couleur (red / green / blue)
*/ 
void color_table_sort(color_table,axis);

/**
* @brief Fonction utilisée pour la fonction de trie, compare par rapport à la composante rouge
* @param a première couleur à comparer
* @param b deuxième couleur à comparer
* @return 0 si les couleurs ont autant de rouge, valeur négative si la première en a moins, positive sinon
*/ 
int compareRed(const void * a, const void * b);

/**
* @brief Fonction utilisée pour la fonction de trie, compare par rapport à la composante vert
* @param a première couleur à comparer
* @param b deuxième couleur à comparer
* @return 0 si les couleurs ont autant de vert, valeur négative si la première en a moins, positive sinon
*/ 
int compareGreen(const void * a, const void * b);

/**
* @brief Fonction utilisée pour la fonction de trie, compare par rapport à la composante bleu
* @param a première couleur à comparer
* @param b deuxième couleur à comparer
* @return 0 si les couleurs ont autant de bleu, valeur négative si la première en a moins, positive sinon
*/ 
int compareBlue(const void * a, const void * b);

/**
* @brief Permet d'afficher une table de couleur
* @param table Prend en entrée une table de couleur
*/
void afficher_table(color_table table);

#endif
