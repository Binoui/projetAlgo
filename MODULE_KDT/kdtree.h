#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "../MODULE_TABLE/table.h"

typedef struct kdtree * kdtree;

typedef enum{r, g, b} axeColor;

kdtree create_kdtree(color_table,int);

void destroy_kdtree(kdtree);

#endif
