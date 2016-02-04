#include "./kdtree.h"

struct kdtree
{
	color_table table;
	kdtree left_son;
	kdtree right_son;
	axis colorAxis;
	int position;	
};


int getAxisMax(color_table table)
{
	int i, sumRed = 0, sumGreen = 0, sumBlue = 0;
	axis axis;
	color colors[3];
	for (i = 0; i < color_table_get_nb_color(table); i++)
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


	return axis;
}

kdtree create_kdtree(color_table table, int limit)
{
	kdtree kdt = malloc(sizeof(struct kdtree));
	kdt->table = table;
	kdt->position = color_table_get_nb_color(table) / 2;


	color_table table_left;
	color_table table_right;

	if (kdt->position >= limit)
	{
		kdt->colorAxis = getAxisMax(kdt->table);	
		color_table_sort(kdt->table, kdt->colorAxis);
		table_left  = color_table_duplicate(table, 0, kdt->position);

		if (kdt->position % 2 == 0)
			table_right = color_table_duplicate(table, kdt->position, kdt->position);
		else
			table_right = color_table_duplicate(table, kdt->position, kdt->position + 1);

		kdt->left_son = create_kdtree(table_left, limit);
		kdt->right_son = create_kdtree(table_right, limit);
	}
	else
	{
		kdt->left_son = NULL;
		kdt->right_son = NULL;
	}

	return kdt;
}

void destroy_kdtree(kdtree kdt)
{
	if (kdt->left_son != NULL)
		destroy_kdtree(kdt->left_son);

	if (kdt->right_son != NULL)
		destroy_kdtree(kdt->right_son);

	destroy_color_table(kdt->table);

	free(kdt);
}

void kdtree_get_nearest_color(kdtree kdt, color * c, color * output)
{	
	color colors[3], saveColor[3];
	int i, vecteurDiffTmp, vecteurDiff, distancePointPlane;
	kdtree othertree;
	if (kdt->left_son == NULL || kdt->right_son == NULL)
	{
		/* On est dans la feuille contenant la couleur la plus proche de c */
		/* Faire une fonction méthode triviale */
		color_table_get_color(kdt->table, 0, colors);
		vecteurDiff = (abs(colors[0] - c[0] +
			               colors[1] - c[1] + 
			               colors[2] - c[2]));

		for (i = 0; i < color_table_get_nb_color(kdt->table); i++)
		{
			color_table_get_color(kdt->table, i, colors);
			vecteurDiffTmp = (abs(colors[0] - c[0] +
				                  colors[1] - c[1] + 
				                  colors[2] - c[2]));

			if (vecteurDiffTmp < vecteurDiff)
			{
				vecteurDiff = vecteurDiffTmp;
				saveColor[0] = colors[0];
				saveColor[1] = colors[1];
				saveColor[2] = colors[2];			
			}
		}
	}
	else
	{
		/* On cherche dans quel fils descendre */
		
		color_table_get_color(kdt->table, kdt->position, colors);

		if (c[kdt->colorAxis] < colors[kdt->colorAxis])
		{
			othertree = kdt->right_son;
			kdtree_get_nearest_color(kdt->left_son, c, output);
		}
		else
		{
			othertree = kdt->left_son;	
			kdtree_get_nearest_color(kdt->right_son, c, output);
		}	

		/* Calcul distance entre couleur cherchée et plan de coupe */	
		vecteurDiff = abs(output[0] - c[0] + 
			              output[1] - c[1] +
		                  output[2] - c[2]);

		color_table_get_color(kdt->table, kdt->position, colors);

		distancePointPlane = (abs(colors[kdt->colorAxis] - c[kdt->colorAxis]));

		saveColor[0] = output[0];
		saveColor[1] = output[1];
		saveColor[2] = output[2];

		if (distancePointPlane < vecteurDiff)
		{
			kdtree_get_nearest_color(othertree, c, colors);

			vecteurDiffTmp = (abs(colors[0] - c[0]) + 
				              abs(colors[1] - c[1]) + 
				              abs(colors[2] - c[2]));

			if (vecteurDiffTmp < vecteurDiff)
			{
				vecteurDiff = vecteurDiffTmp;
				saveColor[0] = colors[0];
				saveColor[1] = colors[1];
				saveColor[2] = colors[2];
			}
		}

	}

	output[0] = saveColor[0];
	output[1] = saveColor[1];
	output[2] = saveColor[2];
}

void afficher_kdtree(kdtree kdt)
{
	afficher_table(kdt->table);

	if (kdt->left_son != NULL)
	{
		printf("\n   GAUCHE   \n");
		afficher_kdtree(kdt->left_son);
		printf("\n   DROITE   \n");
		afficher_kdtree(kdt->right_son);
	}
}
