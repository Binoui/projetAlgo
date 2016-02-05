#include <time.h>
#include "./kdtree.h"
 	
int main(int argc, char *argv[])
{
	image img = FAIRE_image();
	kdtree arbre;

	if (argc < 2)
	{
		printf("erreur, entrez une image en argument puis la table à utiliser\n");
		return EXIT_FAILURE;
	}

	if (image_charger(img, argv[1]) < 0)
	{
		printf("erreur fichier\n");
		return EXIT_FAILURE;
	}

	/*image_charger(img, argv[1]);*/
	image_debut(img);

	image modele = FAIRE_image();
/*	image_charger(modele, "../IMAGES/TABLES/table_lenna_256.ppm");
*/	
	clock_t t1 = clock();
	clock_t t2;
	image_charger(modele, argv[2]);
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

	t2 = clock();
	float time = (float)(t2 - t1) / CLOCKS_PER_SEC;

	printf("Image crée dans newImage.ppm en %f secondes\n", time);
	image_sauvegarder(img, "newImage.ppm");

	destroy_kdtree(arbre);

	return 0;
}