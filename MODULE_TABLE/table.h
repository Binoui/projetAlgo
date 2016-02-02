#ifndef __TABLE_HH__
#define __TABLE_HH__

#include "../MODULE_IMAGE/image.h"

typedef enum {red,green,blue} axis;
typedef unsigned char color; /* UNSIGNED CHAR PLUTOT QUE CHAR OU INT */
typedef enum {false,true} boolean;

typedef struct color_table * color_table;

typedef int (*FCT_CMP)(const void *, const void *);

color_table create_color_table(image);

boolean destroy_color_table(color_table);

color_table color_table_duplicate(color_table,int,int);

void color_table_get_color(color_table,int,color*);

int color_table_get_nb_color(color_table);

void color_table_sort(color_table,axis);

int compareRed(const void * a, const void * b);

int compareGreen(const void * a, const void * b);

int compareBlue(const void * a, const void * b);

void afficher_table(color_table table);

void exchangeVal(color * table, int i, int j);

int part(color * table, int start, int end, FCT_CMP fctCmp);

void sortTable(color *table, int sortStart, int sortEnd, FCT_CMP fctCmp);

#endif