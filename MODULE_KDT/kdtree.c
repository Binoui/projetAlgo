#include "./kdtree.h"

struct kdtree
{
	color_table table;
	kdtree left_son;
	kdtree right_son;
	axis colorAxis;
	int position;	
};

kdtree create_kdtree(color_table table, int limit)
{
	kdtree kdt = malloc(sizeof(kdtree));
	kdt->table = table;
	kdt->position = color_table_get_nb_color(table) / 2;
	printf("récursif\n");

	int i, sumRed, sumGreen, sumBlue;
	color * colors = malloc(3*sizeof(color));
	for (i = 0; i < color_table_get_nb_color(kdt->table); i++)
	{
		color_table_get_color(table, i, colors);
		sumRed   += colors[0];
		printf("%d %d %d\n", i, colors[1], sumGreen);
		sumGreen += colors[1];
		sumBlue  += colors[2];
	}
	printf("récursif\n");
	printf("%d\n",sumRed);
	printf("%d\n",sumGreen);
	printf("%d\n",sumBlue );
	if (sumRed > sumGreen)
		if (sumRed > sumBlue)
			kdt->colorAxis = red;
		else
			kdt->colorAxis = blue;
	else
		if (sumGreen > sumBlue)
			kdt->colorAxis = green;
		else
			kdt->colorAxis = blue;




	color_table_sort(kdt->table, kdt->colorAxis);

	color_table table_left;
	color_table table_right;

	printf("récursif\n");
	if (kdt->position >= limit)
	{
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

int main(int argc, char *argv[])
{
/*	image table = FAIRE_image();
*/	kdtree arbre;

	if (argc < 1)
	{
		printf("erreur, entrez une image en argument\n");
		return EXIT_FAILURE;
	}

/*	if (image_charger(table, argv[1]) < 0)
	{
		printf("erreur fichier\n");
		return EXIT_FAILURE;
	}*/

	image img = FAIRE_image();
	image_charger(img, "../IMAGES/TABLES/table_house_512.ppm");
	image_debut(img);

	color_table table = create_color_table(img);

	printf("%d\n", table == NULL);

	arbre = create_kdtree(table, 10);

	return 0;
}

