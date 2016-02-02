#include "./table.h"

struct color_table
{
	color * colors;
	int size;
	boolean owner;
};

color_table create_color_table(image img)
{
	assert(img != NULL);	

	color_table table = malloc(sizeof(color_table));

	table->size   = image_give_largeur(img)*image_give_dim(img);
	table->colors = malloc(sizeof(color) * table->size);
	table->owner  = true;

	image_debut(img);

	int * pixel, i;
	do 
	{
		pixel = image_lire_pixel(img);
		table->colors[i] = (color) (pixel[0]);
		table->colors[i+1] = (color) (pixel[1]);
		table->colors[i+2] = (color) (pixel[2]);
		i+=3;
	} while (image_pixel_suivant(img) != faux);

	return table;
}

boolean destroy_color_table(color_table table)
{
	if (table != NULL)
		return false;

	if (table->owner == true)
	{
		free(table->colors);
		table->colors = NULL;
		table->size = 0;
	}

	free(table);
	table = NULL;

	return true;
}

color_table color_table_duplicate(color_table table, int offset, int length)
{
	assert(table != NULL && offset >= 0 && offset < table->size && length >= 0 && length < table->size);

	color_table table2 = malloc(sizeof(color_table));
	table2->size   = length*3;
	table2->colors = (table->colors) + 3 * offset;
	table2->owner = false;

	return table2;
}

void color_table_get_color(color_table table, int index, color * colors)
{
	assert(table != NULL && index >= 0 && index < table->size);

	index*=3;

	colors[0] = table->colors[index++];
	colors[1] = table->colors[index++];
	colors[2] = table->colors[index];
}

int color_table_get_nb_color(color_table table)
{
	return table->size / 3;
}

void exchangeVal(color * table, int i, int j)
{	
	color tmp;
	tmp = table[j];
	table[j] = table[i];
	table[i] = tmp;	
}

int part(color * table, int start, int end, FCT_CMP fctCmp)
{
	int i, j = start;
	color x = table[start];

	for (i = start + 1; i <= end ; i+=3)
	{
		if (fctCmp(&table[i], &x) < 0)
		{
			j++;
			exchangeVal(table, j, i);
		}
	}

	exchangeVal(table,j,start);
	
	return j;
}

void sortTable(color * table, int sortStart, int sortEnd, FCT_CMP fctCmp)
{
	int i;
	
	if (sortStart < sortEnd)
	{
		i = part(table, sortStart, sortEnd, fctCmp);
		sortTable(table, sortStart, i-1, fctCmp);
		sortTable(table, i+1, sortEnd, fctCmp);		
	}
}

void color_table_sort(color_table table, axis colorAxis)
{
	assert(table != NULL && colorAxis >= 0 && colorAxis <= 2);

	switch (colorAxis)
	{
		case red : 
    		sortTable(table->colors, 0, table->size - 1, compareRed); 
		break;

		case green : 
    		sortTable(table->colors, 0, table->size - 1, compareGreen); 
		break;

		case blue : 
    		sortTable(table->colors, 0, table->size - 1, compareBlue); 
		break;
	}
}
/*
void color_table_sort(color_table table, axis axis)
{
	assert(table != NULL && axis >= 0 && axis <= 2);
	printf("table : %p\n", table);
	switch (axis)
	{
		case red : 
			qsort(table->colors, table->size, 3*sizeof(color), compareRed);
		break;

		case green : 
			qsort(table->colors, table->size, 3*sizeof(color), compareGreen);
		break;

		case blue : 
			qsort(table->colors, table->size, 3*sizeof(color), compareBlue);
		break;
	}
}
*/
int compareRed(const void * a, const void * b)
{
	int colA = *((const color *) a);
	int colB = *((const color *) b);

	return (int) colA - colB;
}

int compareGreen(const void * a, const void * b)
{
	int colA = *((const color *) a + 1);
	int colB = *((const color *) b + 1);

	return colA - colB;
}

int compareBlue(const void * a, const void * b)
{
	int colA = *((const color *) a + 2);
	int colB = *((const color *) b + 2);

	return colA - colB;
}

void afficher_table(color_table table)
{
	int i;
	for (i = 0; i < color_table_get_nb_color(table)*3; i+=3)
	{
		printf("color %d : %d %d %d\n", i/3, table->colors[i], table->colors[i+1], table->colors[i+2]);
	}
	printf("\n");
}

int main()
{
	image img = FAIRE_image();
	image_charger(img, "../IMAGES/TABLES/table_lenna_256.ppm");

	color_table table = create_color_table(img);

	printf("Nombre de couleurs dans la table : %d\n", color_table_get_nb_color(table));

	printf("table : \n");
	afficher_table(table);

	printf("Tri table\n");
	color_table_sort(table, blue);
	afficher_table(table);	

/*	color_table table2 = color_table_duplicate(table, 7, 4);

	
	printf("table 2 : \n");
	afficher_table(table2);

	int ind = 237;
	printf("Color %d : \n", ind);
	color colors[3];
	color_table_get_color(table, ind, colors);
	printf("Ligne %d : %d %d %d\n\n", ind, colors[0], colors[1], colors[2]);

	destroy_color_table(table2);

	printf("Tri table\n");
	color_table_sort(table, blue);
	afficher_table(table);	

	destroy_color_table(table);*/

	return 0;
}