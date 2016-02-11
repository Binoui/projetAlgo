#include "./MODULE_IMAGE/image.h"
#include "./MODULE_TABLE/table.h"

#include <math.h>
#include <time.h>

struct color_table
{
	color * colors;
	int size;
	boolean owner;
};

int main(int argc, char *argv[])
{
	
		if (argc != 3)
		{
			printf("Entrez en argument l'image modèle puis l'image contenant la table à utilsier\n");
			return 1;
		}

		int i, vecteurDiff, vecteurDiffTmp;
		color * colors = malloc(3*sizeof(color));
		int * pixel;
		int colorMin[3];

		image origine = FAIRE_image();
/*		image_charger(origine, "./IMAGES/TABLES/table_lenna_1280.ppm");*/

		if (image_charger(origine, argv[2]) < 0)
		{
			printf("erreur fichier\n");
			return EXIT_FAILURE;
		}

		color_table table = create_color_table(origine);

		clock_t t1 = clock();
		clock_t t2;

		image modele = FAIRE_image();
		/*image_charger(modele, "./IMAGES/lenna.ppm");	*/
		image_charger(modele, argv[1]);
		image_debut(modele);


		do
		{
			pixel = image_lire_pixel(modele);

			color_table_get_color(table, 0, colors);
			vecteurDiff = (abs(colors[0] - pixel[0]) + 
				abs(colors[1] - pixel[1]) + 
				abs(colors[2] - pixel[2]));

			colorMin[0] = colors[0];
			colorMin[1] = colors[1];
			colorMin[2] = colors[2];


			for (i = 1; i < color_table_get_nb_color(table); i++)
			{
				color_table_get_color(table, i, colors);
				vecteurDiffTmp = (abs(colors[0] - pixel[0]) + 
					abs(colors[1] - pixel[1]) + 
					abs(colors[2] - pixel[2]));

				
				if (vecteurDiffTmp < vecteurDiff)
				{
					vecteurDiff = vecteurDiffTmp;
					colorMin[0] = colors[0];
					colorMin[1] = colors[1];
					colorMin[2] = colors[2];
				}
			}

			image_ecrire_pixel(modele, colorMin);

		} while (image_pixel_suivant(modele) != faux);

		t2 = clock();
		float time = (float)(t2 - t1) / CLOCKS_PER_SEC;

		printf("Nouvelle image newImage.ppm créée en %f secondes\n", time);
		image_sauvegarder(modele, "newImage.ppm");

		return 0;
	}