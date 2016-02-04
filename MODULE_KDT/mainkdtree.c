#include "./kdtree.h"

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
	image_charger(img, "../IMAGES/lenna.ppm");
	image_debut(img);

	image modele = FAIRE_image();
	image_charger(modele, "../IMAGES/TABLES/table_lenna_1280.ppm");
	image_debut(modele);


	color_table table = create_color_table(modele);

	arbre = create_kdtree(table, 10);

/*	afficher_kdtree(arbre); 
*/
	int * pixel;
	color newColors[3];
	color colors[3];
	int newPixel[3];

	do
	{
		pixel = image_lire_pixel(img);

		colors[0] = (color) pixel[0];
		colors[1] = (color) pixel[1];
		colors[2] = (color) pixel[2];

		newColors[0] = 255;
		newColors[1] = 255;
		newColors[2] = 255;

		kdtree_get_nearest_color(arbre, colors, newColors);

		newPixel[0] = (int) newColors[0];
		newPixel[1] = (int) newColors[1];
		newPixel[2] = (int) newColors[2];

		image_ecrire_pixel(img, newPixel);
	} while (image_pixel_suivant(img) != faux);

	image_sauvegarder(img, "image.ppm");

	destroy_kdtree(arbre);

	return 0;
}