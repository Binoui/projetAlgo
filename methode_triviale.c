#include "./MODULE_IMAGE/image.h"
#include "./MODULE_TABLE/table.h"

#include <math.h>

struct color_table
{
	color * colors;
	int size;
	boolean owner;
};

int main(int argc, char *argv[])
{
/*	if (argc != 3)
	{
		printf("Entrez en argument une image contenant la table à charger et une image à utiliser comme modèle\n");
		return 1;
	}*/

	int i, vecteurDiff, vecteurDiffTmp, indColor = 0;
	int colors_image[3];
	color * colors = malloc(3*sizeof(color));
	int * pixel;
	int colorMin[3];

	image origine = FAIRE_image();
	image_charger(origine, "./IMAGES/TABLES/table_house_1280.ppm");
	/*image_charger(origine, argv[1]);*/
	color_table table = create_color_table(origine);

	image modele = FAIRE_image();
	image_charger(modele, "./IMAGES/zelda.ppm");	
	image_debut(modele);
	/*image_charger(modele, argv[2]);*/

	int nbPix = 0;
	do
	{
		pixel = image_lire_pixel(modele);
		// printf("pixel %d : %d %d %d\n", nbPix++, pixel[0], pixel[1], pixel[2]);

		color_table_get_color(table, 0, colors);
		vecteurDiff = (abs(colors[0] - pixel[0]) + 
		              abs(colors[1] - pixel[1]) + 
			          abs(colors[2] - pixel[2]));

		colorMin[0] = colors[0];
		colorMin[1] = colors[1];
		colorMin[2] = colors[2];
	
		// printf("vecteurDiff : %d\n", vecteurDiff);

		for (i = 1; i < color_table_get_nb_color(table); i++)
		{
			// printf("coor nb %d / %d\n", i, color_table_get_nb_color(table));
			color_table_get_color(table, i, colors);
			// printf("colors %d : %d %d %d\n", i, colors[0], colors[1], colors[2]);
			vecteurDiffTmp = (abs(colors[0] - pixel[0]) + 
			               abs(colors[1] - pixel[1]) + 
				           abs(colors[2] - pixel[2]));

			// printf("vect diff tmp : %d\n", vecteurDiffTmp);

			// printf("Comparaison vec : %d tmp : %d\n", vecteurDiff, vecteurDiffTmp);

			if (vecteurDiffTmp < vecteurDiff)
			{
				// printf("changement vecteur diff\n");
				vecteurDiff = vecteurDiffTmp;
				colorMin[0] = colors[0];
				colorMin[1] = colors[1];
				colorMin[2] = colors[2];
				// printf("pix : %d %d %d\n", pixel[0], pixel[1], pixel[2]);
			}
		}

		// printf("fin vecteurDiff : %d\n", vecteurDiff);


		image_ecrire_pixel(modele, colorMin);

	} while (image_pixel_suivant(modele) != false);

	image_sauvegarder(modele, "newZelda.ppm");

	return 0;
}