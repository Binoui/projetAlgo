#include "./kdtree.h"

struct kdtree
{
	color_table table;
	kdtree * left_son;
	kdtree * right_son;
	axis axis;
	int position;	
};

kdtree create_kdtree(color_table table, int limit)
{
	kdtree kdt = malloc(sizeof(kdtree));
	kdt->table = table;
	kdt->position = color_table_get_nb_color(table) / 2


	int i, sumRed, sumGreen, sumBlue, * colors;
	for (i = 0; i < color_table_get_nb_color(kdt->table); i++)
	{
		color_table_get_color(table, i, colors);
		sumRed   += colors[0];
		sumGreen += colors[1];
		sumBlue  += colors[2];
	}

	if (sumRed > sumGreen)
		if (sumRed > sumBlue)
			axis = red;
		else
			axis = blue;
	else
		if (sumGreen > sumBlue)
			axis = green;
		else
			axis = blue;


	color_table_sort(table, axis);

	if (kdt->position >= limite)
	{

	}
	else
	{
		left_son = NULL;
		right_son = NULL;
	}


}