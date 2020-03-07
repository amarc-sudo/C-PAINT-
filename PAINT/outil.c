/*
 * outil.c
 *
 * Copyright 2019 aurel <aurel@debian>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include "outil.h"
#include "global.h"
#include "couleur.h"
#include <math.h>


//fonction void qui dessine en temps réel
//je prend un point vérification pour la récursivité. si jamais je reviens dans la fonction cela me permet de ne pas tracer une ligne entre l'endroit ou j'ai cliquer et l'endroit ou je commence a déssiner 
// LA fonction attend un clic avant de commencer, 
// si le clic est dans la zone de dessin alors :
// 	la fonction dessine un trait entre deux points qui son récupérer au fur et a messure
// si le clic est dans une zone de palette alors la fonction change la couleur et reviens dans la fonction de dessin
// si le clic est en dehors de tout alors la fonction se fini 
void crayon(Point verification)
{
	Point pixel = {0,0}, pixel2 = {0,0},p; 
	int i = 1;
	p = attendre_clic(); //on attend le premier clic pour commencer à dessiner
	if(((p.x > 0 && p.x < 1000) && (p.y > 0 && p.y < 100))||((p.x > 0 && p.x < 200) && (p.y > 0 && p.y < 700))) //si le premier clic est en dehors on annule tout
		i = 0;

	if(verification_couleur(p))
	{
		selection_couleur(p);
		crayon(verification);
	}
	else if(verification_taille(p))
	{
		changement_taille(p);
		crayon(verification);
	}
	p.x = 0;
	p.y = 0;
	while(i)
	{
		reinitialiser_evenements();
		pixel = deplacement_souris_a_eu_lieu();
		traiter_evenements();

		//le point verification prend tout son sens. si le point est le même que celui auquel j'étais la dernière fois je ne trace pas de ligne
		//sans ce point verification cela me tracet des lignes un peu partout.
		if(verification_plateau(pixel)&&verification_plateau(pixel2) && verification.x != pixel2.x && verification.y != pixel2.y)
		{
			dessiner_ligne(pixel,pixel2,couleurchoisi);
			trait_plus_gros(pixel,pixel2);
			actualiser();
			verification.x = 0;
			verification.y = 0;
		}

		reinitialiser_evenements();
		pixel2 = deplacement_souris_a_eu_lieu();
		traiter_evenements();

		p = clic_a_eu_lieu();
		traiter_evenements();

		//si il y a eu un clic je rentre dans cette boucle. elle me permet d'arrete de dessiner.
		if(verification_plateau(p))
		{
			afficherinstruction("Pour continuer de dessiner, recliquer sur la zone blanche, sinon double-cliquer en dehors",15);
			verification = pixel2;
			crayon(verification);//je fais du recursif
			i = 0;//quand on reviendra à cette fonction on stopera son processus
		}
		
	}
		reinitialiser_evenements();
		//printf("%d %d pixel \n %d %d pixel2",pixel.x, pixel.y, pixel2.x, pixel2.y);
}


//même principe que le crayon. je ne réexpliquerais pas son fonctionnement
void gomme(Point verification)
{
	Point pixel = {0,0};
	Point pixel2 = {0,0};
	Point p; //on crée plusieurs points pour verifier des conditions
	int i=1;
	p = attendre_clic();
	 //on attend le premier clic pour commencer à dessiner
	if(((p.x > 0 && p.x < 1000) && (p.y > 0 && p.y < 100))||((p.x > 0 && p.x < 200) && (p.y > 0 && p.y < 700))) //si le premier clic est en dehors on annule tout
		i = 0;
	if(verification_couleur(p))
	{
		selection_couleur(p);
		gomme(verification);
	}
	else if(verification_taille(p))
	{
		changement_taille(p);
		gomme(verification);
	}
	while(i)//je rentre dans la boucle
	{
				reinitialiser_evenements();
				pixel = deplacement_souris_a_eu_lieu();
				traiter_evenements();


				if(verification_plateau(pixel)&&verification_plateau(pixel2) && verification.x != pixel2.x && verification.y != pixel2.y)
					{
					dessiner_ligne(pixel,pixel2,blanc);
					actualiser();
					gomme_plus_grosse(pixel, pixel2);
					verification.x = 0;
					verification.y = 0;
					}

					reinitialiser_evenements();
					pixel2 = deplacement_souris_a_eu_lieu();
					traiter_evenements();


					p = clic_a_eu_lieu();
					traiter_evenements();
					if(verification_plateau(p))
						{
							verification = pixel2;
							gomme(verification);//je fais du recursif
							i = 0;//quand on reviendra à cette fonction on stopera son processus
						}
					reinitialiser_evenements();
				//printf("%d %d pixel \n %d %d pixel2",pixel.x, pixel.y, pixel2.x, pixel2.y);
			}
}

// Fonction void de tracage de ligne
// ne demande rien
// demande 2 points, fait les vérifications habituelles et trace une ligne entre les deux points
void ligne()
{
	Point p1, p2;
	p1 = attendre_clic();
	if(verification_plateau(p1))
	{
		p2 = attendre_clic();
		if(verification_plateau(p2))

		{
			dessiner_ligne(p1, p2, couleurchoisi);
			trait_plus_gros(p1,p2);
			actualiser();
		}
		if(verification_couleur(p2))
		{
			selection_couleur(p2);
			ligne();
		}
		else if(verification_taille(p2))
		{
			changement_taille(p2);
			ligne();
		}
	}
	if(verification_couleur(p1))
	{
		selection_couleur(p1);
		ligne();
	}
	else if(verification_taille(p1))
	{
		changement_taille(p1);
		ligne();
	}
}

// Fonction void de tracage de triangle
// ne demande rien
// demande 3 points, fait les verifications habituelles et trace une ligne entre les deux points
void dessiner_triangle()
{
	Point p1, p2, p3;
	p1 = attendre_clic();
	if(verification_plateau(p1))
	{
		p2=attendre_clic();

		if (verification_plateau(p2))
		{
			dessiner_ligne(p1 , p2 , couleurchoisi);
			trait_plus_gros(p1, p2);
			actualiser();
			p3 = attendre_clic();
			if(verification_plateau(p3))
			{
				dessiner_ligne(p2 , p3 , couleurchoisi);
				trait_plus_gros(p2, p3);
				dessiner_ligne(p3 , p1 , couleurchoisi);
				trait_plus_gros(p3, p1);
			}
			else if (verification_couleur(p3))
			{
				selection_couleur(p3);
				und(enregistrement);
				actualiser();
				dessiner_triangle();
			}
			else if (verification_taille(p3))
			{
				changement_taille(p3);
				und(enregistrement);
				actualiser();
				dessiner_triangle();
			}
			else
			{
				und(enregistrement);
				actualiser();
			}
		}

		else if (verification_couleur(p2))
		{
			selection_couleur(p2);
			und(enregistrement);
			actualiser();
			dessiner_triangle();
		}
		else if (verification_taille(p2))
		{
			changement_taille(p2);
			und(enregistrement);
			actualiser();
			dessiner_triangle();
		}
		else
		{
			und(enregistrement);
			actualiser();
		}

	}

	else if (verification_couleur(p1))
	{
		selection_couleur(p1);
		und(enregistrement);
		dessiner_triangle();
	}
	else if (verification_taille(p1))
	{
		changement_taille(p1);
		und(enregistrement);
		actualiser();
		dessiner_triangle();
	}
}

// Fonction void de tracage de triangle PLEIN
// ne demande rien
// demande 3 points, fait les verifications habituelles et trace une ligne entre les trois points
// Ensuite elle parcourt toutes la zone de dessin et vérifie si les points sont dans le triangle. Si ils y sont alors elle change le point
void dessiner_triangle_plein()
{
	int point_dans_trianlge_bool = 0;
	Point p1, p2, p3, ptest = {0,0};
	p1 = attendre_clic();
	if(verification_plateau(p1))
	{
		p2=attendre_clic();
		if (verification_plateau(p2))
		{
			dessiner_ligne(p1 , p2 , couleurchoisi);
			trait_plus_gros(p1, p2);
			actualiser();
			p3 = attendre_clic();
			if(verification_plateau(p3))
			{
				dessiner_ligne(p1 , p2 , couleurchoisi);
				dessiner_ligne(p2 , p3 , couleurchoisi);
				dessiner_ligne(p3 , p1 , couleurchoisi);
				//je parcours toute la zone. si un point est dans le triangle je change ca couleur
				for(ptest.y = 100; ptest.y < 700; ptest.y++)
				{
					for(ptest.x = 200; ptest.x < 1000; ptest.x++)
					{
					point_dans_trianlge_bool = point_dans_triangle(p1, p2, p3, ptest);
					if(point_dans_trianlge_bool)
						changer_pixel(ptest,couleurchoisi);
					}
				}
			}
			else if (verification_couleur(p3))
			{
				selection_couleur(p3);
				und(enregistrement);
				actualiser();
				dessiner_triangle_plein();
			}
			else
			{
				und(enregistrement);
				actualiser();
			}
		}

		else if (verification_couleur(p2))
		{
			selection_couleur(p2);
			und(enregistrement);
			actualiser();
			dessiner_triangle_plein();
		}
		else
		{
			und(enregistrement);
			actualiser();
		}

	}
	else if (verification_couleur(p1))
	{
		selection_couleur(p1);
		und(enregistrement);
		dessiner_triangle_plein();
	}
}
// Fonction void de tracage de polygone VIDE
// ne demande rien
// demande deux points au départ et trace une ligne entre ces deux points
// ensuite demande un troisième points et trace une ligne entre le deuxième et le troisième points
// remplace le deuxième par le troisième points
// redemande un troisième...
// continue ainsi jusqu'a un clic hors de la zone ou un clic droit

void polygonevide()
{
	int i = 1;
	Point p1, p2, p3;
	p1 = attendre_clic_gauche_droite();
	if (verification_plateau(p1))
	{
		p2 = attendre_clic_gauche_droite();
		if (verification_plateau(p2))
		{
			dessiner_ligne(p1, p2, couleurchoisi);
			trait_plus_gros(p1, p2);
			actualiser();
			while(i)
			{
				p3 = attendre_clic_gauche_droite();
				if(verification_plateau(p3))
				{
				dessiner_ligne(p2, p3, couleurchoisi);
				trait_plus_gros(p2, p3);
				actualiser();
				p2 = p3;
				}
				else
				 i = 0;
			}
			dessiner_ligne(p1, p2, couleurchoisi);
			trait_plus_gros(p1, p2);
		}
		else if(verification_couleur(p2))
		{
			sauvegarder(enregistrement);
			selection_couleur(p2);
			polygonevide();
		}
		else if(verification_taille(p2))
		{
			changement_taille(p2);
			polygonevide();
		}
	}
	else if (verification_couleur(p1))
	{
		sauvegarder(enregistrement);
		selection_couleur(p1);
		polygonevide();
	}
	else if(verification_taille(p1))
	{
		changement_taille(p1);
		polygonevide();
	}
}
// Fonction void de tracage de polygone VIDE
// ne demande rien
// demande deux points au départ et trace une ligne entre ces deux points
// ensuite demande un troisième points et trace une triangle plein entre le premier, le deuxième et le troisième points
// remplace le premier point par le deuxième et le deuxième par le troisième points
// redemande un troisième point...
// continue ainsi jusqu'a un clic hors de la zone ou un clic droit
void polygone_plein()
{
	int i = 1, dans_poly;
	Point p1, p2, p3, ptest;
	p1 = attendre_clic_gauche_droite();
	if (verification_plateau(p1))
	{
		p2 = attendre_clic_gauche_droite();
		if (verification_plateau(p2))
		{
			dessiner_ligne(p1, p2, couleurchoisi);
			actualiser();
		

			while(i)
			{
				p3 = attendre_clic_gauche_droite();
				//
				//je créé un nouveau triangle entre le nouveau point et les deux précédents points
				//
				if(verification_plateau(p3))
				{
					dessiner_ligne(p2, p3, couleurchoisi);
					for(ptest.y = 100; ptest.y < 700; ptest.y++)
					{
						for(ptest.x = 200; ptest.x < 1000; ptest.x++)
						{
							dans_poly = point_dans_triangle(p1, p2, p3, ptest);
							if(dans_poly)
							{changer_pixel(ptest,couleurchoisi);}
						}
					}
					actualiser();
					p1 = p2;
					p2 = p3;
				}
				else if (verification_couleur(p2))
				{
					selection_couleur(p2);
					polygone_plein();
				}	
				else
				i = 0;
			}
		}
		else if (verification_couleur(p2))
		{
			selection_couleur(p2);
			polygone_plein();
		}	
	}
	else if (verification_couleur(p1))
	{
		selection_couleur(p1);
		polygone_plein();
	}
}


// Fonction void de tracage de cercle VIDE
// ne demande rien
// demande 2 points, fait les vérifications habituelles et trace un cercle entre les deux points
void cercle()
{
	Point coinhaut = {0,0}, coingauche = {0,100};
	Point couleurchanger = {115, 60};
	Point centre, rayon1, rayon2;
	int rayonducercle;
	rayon1 = attendre_clic();
	if(verification_plateau(rayon1))
	{
		rayon2 = attendre_clic();
		if(verification_plateau(rayon2))
		{	
			centre.x = (rayon1.x + rayon2.x)/2;
			centre.y = (rayon1.y + rayon2.y)/2;
			rayonducercle =	(sqrt(pow((rayon2.x-rayon1.x),2)+pow((rayon2.y-rayon1.y),2))/2);
			dessiner_cercle(centre, rayonducercle, couleurchoisi);
			cercle_plus_gros(centre,rayonducercle);
			afficher_image("image/haut.bmp", coinhaut);
			afficher_image("image/gauche.bmp", coingauche);
			dessiner_rectangle(couleurchanger,72,31, couleurchoisi);
			indication_taille();
		}	
		else if(verification_taille(rayon2))
		{
		changement_taille(rayon2);
		cercle();
		}
		else if(verification_couleur(rayon2))
		{
		selection_couleur(rayon2);
		cercle();
		}
	}
	else if(verification_taille(rayon1))
	{
		changement_taille(rayon1);
		cercle();
	}
	else if(verification_couleur(rayon1))
	{
		selection_couleur(rayon1);
		cercle();
	}
}

// Fonction void de tracage de cercle PLEIN
// ne demande rien
// demande 2 points, fait les vérifications habituelles et trace un cercle entre les deux points
void disque()
{
	Point coinhaut = {0,0}, coingauche = {0,100};
	Point couleurchanger = {115, 60};	
	Point centre, rayon1, rayon2;
	int rayonducercle;
	rayon1 = attendre_clic();
	if(verification_plateau(rayon1))
	{
		rayon2 = attendre_clic();
		if(verification_plateau(rayon2))
		{	
			centre.x = (rayon1.x + rayon2.x)/2;
			centre.y = (rayon1.y + rayon2.y)/2;
			rayonducercle =	(sqrt(pow((rayon2.x-rayon1.x),2)+pow((rayon2.y-rayon1.y),2))/2);
			dessiner_disque(centre, rayonducercle, couleurchoisi);
			afficher_image("image/haut.bmp", coinhaut);
			afficher_image("image/gauche.bmp", coingauche);
			dessiner_rectangle(couleurchanger,72,31, couleurchoisi);
			indication_taille();
		}
		else if(verification_couleur(rayon2))
		{
			selection_couleur(rayon2);
			disque();
		}
	}
	else if(verification_couleur(rayon1))
	{
		selection_couleur(rayon1);
		disque();
	}
}

// Fonction void qui désinne un rectangle
// Demande deux points, si ils sont dans la zone de dessin
// cela appelle la fonction dessiner_rectangle_par_les_coins
// qui va dessiner un rectangle qu'importe soit l'ordre des clic.
void rectangle()
{
	Point p1, p2;
	p1 = attendre_clic();
	if(verification_plateau(p1))
	{
		p2 = attendre_clic();
		if(verification_plateau(p2))
			dessiner_rectangle_par_coins(p1, p2);
		
		else if (verification_couleur(p2))
		{
			sauvegarder(enregistrement);
			selection_couleur(p2);
			rectangle();
		}
	}

	else if (verification_couleur(p1))
	{
		sauvegarder(enregistrement);
		selection_couleur(p1);
		rectangle();
	}
}
//Fonction void qui va dessiner un rectangle. 
//prend deux points en arguments
void dessiner_rectangle_par_coins (Point p1, Point p2)
{
    Point p;
    if ((p1.x < p2.x) && (p1.y < p2.y)) 
    	dessiner_rectangle (p1, (p2.x - p1.x), (p2.y - p1.y), couleurchoisi);
    else if ((p1.x > p2.x) && (p1.y > p2.y)) 
    	dessiner_rectangle (p2, (p1.x - p2.x), (p1.y - p2.y), couleurchoisi);
    else if ((p1.x < p2.x) && (p1.y > p2.y))
    {
        p.x = p1.x; p.y = p2.y; 
        dessiner_rectangle (p, (p2.x - p.x), (p1.y - p.y), couleurchoisi);
    }
    else if ((p1.x > p2.x) && (p1.y < p2.y))
    {
        p.x = p2.x; p.y = p1.y; 
        dessiner_rectangle (p, (p1.x - p.x), (p2.y - p.y), couleurchoisi);
    }
}

//fonction void qui va dessiner un rectangle VIDE
//ne prend rien
//va demander deux points via des clic et dessiner un rectangle VIDE 
//elle appelle la fonction tracer_rectangle_vide
void rectanglevide()
{
	Point coin1, coin2,coin3, coin4;
	coin1 = attendre_clic();
	
	if(verification_couleur(coin1))
	{
		selection_couleur(coin1);
		rectanglevide();
	}
	
	else if(verification_taille(coin1))
	{
		changement_taille(coin1);
		rectanglevide();
	}

	else if (verification_plateau(coin1))
	{
		coin2 = attendre_clic();

		if(verification_couleur(coin2))
		{
		selection_couleur(coin2);
		rectanglevide();
		}
	
		else if(verification_taille(coin2))
		{
			changement_taille(coin2);
			rectanglevide();
		}

		else if (verification_plateau(coin2))
		{
			coin3.x = coin2.x;
			coin3.y = coin1.y;
			coin4.x = coin1.x;
			coin4.y = coin2.y;
			tracer_rectangle_vide(coin1,coin2,coin3,coin4);
		}
	}
}

// Fonction void qui va dessiner un rectangle vide
// prend quatre points en argument
// dessine des ligne entre ces 4 points
void tracer_rectangle_vide(Point p1, Point p2, Point p3, Point p4)
{
	dessiner_ligne(p1, p3, couleurchoisi);
	trait_plus_gros( p1, p3);
	dessiner_ligne(p3, p2, couleurchoisi);
	trait_plus_gros( p3, p2);
	dessiner_ligne(p2, p4, couleurchoisi);
	trait_plus_gros( p2, p4);
	dessiner_ligne(p4, p1, couleurchoisi);
	trait_plus_gros(p4,p1);
}

// Fonction de pipette
// ne prend rien
// attend un clic et prend la couleur de ce clic
void pipette()
{
	Point pipette, couleurchanger = {115, 60};
	pipette = attendre_clic();
	if(verification_plateau(pipette))
	{
		couleurchoisi = couleur_point(pipette);
		dessiner_rectangle(couleurchanger,72,31, couleurchoisi);	
		actualiser();
	}
}

//fonction void d'affichage d'image.
// ne prend rien
// demande a l'utilisateur un nom d'image
// vérifie si elle existe. si elle n'existe pas. fais une sauvegarde et l'enregistre en backup.bmp
// si elle existe il l'affiche a l'endroit souhaiter via un clic
void afficher_image_choisi()
{
	char nom_image[40];
	Point image;
	printf("rentrez le nom de l'image\n");
	scanf("%s", nom_image);
	FILE *f=fopen(nom_image,"r");
    if(!f)
        {
        sauvegarder(enregistrement);
        enregistre_bmp(enregistrement,"backup.bmp");
        fprintf(stderr,"Erreur: le chemin '%s' ne mene a aucune image valable pour etre ouverte\n",nom_image);
        exit(1);
        }
    fclose(f);
    image = attendre_clic();
    afficher_image(nom_image, image);
}
//fonction de sauvegarde (void)
//prend en entrée le tableau de sauvegarde
//pour toute la longueur et toutes la largeur de la zone de dessins. mets les pixels dans un tableau de 800 sur 600
void sauvegarder(int enregistrement[LARGEURTABLEAU][HAUTEURTABLEAU])
{
	int h, l;
	Point coul = {POSX,POSY};
	for (h = 0 ; h < HAUTEURTABLEAU ; h ++ )
	{
		for(l = 0 ; l < LARGEURTABLEAU ; l ++)
		{
			enregistrement[l][h]= couleur_point(coul);
			coul.x++;
		}
	coul.y++;
	coul.x = POSX;
	}
}

//fonction de undo (void)
//prend en entrée le tableau de sauvegarde
//pour toute la longueur et toutes la largeur de la zone de dessin. mets les couleurs présentes dans le tableau dans la zone de dessin
void und(int enregistrement[LARGEURTABLEAU][HAUTEURTABLEAU])
{
	int h, l;
	Point coul = {POSX,POSY};
	for (h = 0 ; h < HAUTEURTABLEAU ; h ++ )
	{
		for(l = 0 ; l < LARGEURTABLEAU ; l ++)
		{
		changer_pixel(coul,enregistrement[l][h]);
		coul.x++;
		}
	coul.y++;
	coul.x = POSX;
	}
}

// Fonction de clear (void)
// Dessine un carré blanc dans la zone de dessin
void clear()
{
	Point clear = {200,100};
	dessiner_rectangle(clear,800,600,blanc);
}

// Fonction de remplisage (void)
// Prend un Point en argument
// pour x++, x--, y++, y--, verifie si la couleur n'est pas la couleurchoisi ou la couleur actuelle.
// si ces conditions sont verifiées remplace le pixel par la couleurchoisi et se rappelle elle même
void remplissage(Point pixel)
{
	int xgauche,xdroite; //on initialise les maximums de droite et les maximums de gauche
	Point pixel2 = pixel; //on initialise des points
	Point pixel3 = pixel;
	//conditions d'arret
	if (couleur_point(pixel) !=couleurchoisi && couleur_point(pixel) ==couleuractuelle)
  	{
		changer_pixel(pixel,couleurchoisi); //on change le pixel actuel
		pixel2.x = xgauche =pixel.x-1; //on va sur le pixel sur la gauche
	   while(pixel2.x>200 && couleur_point(pixel2)!=couleurchoisi && couleur_point(pixel2 )== couleuractuelle) //on recherche a la valeur maximale de gauche
		{
			changer_pixel(pixel2,couleurchoisi);
			pixel2.x--;
		}
		xgauche = pixel2.x;
		pixel2.x = xdroite = pixel.x+1;
	  while(pixel2.x<1000 && couleur_point(pixel2)!=couleurchoisi && couleur_point(pixel2 )== couleuractuelle) //on recherche la valeur maximale de droite
		{
			changer_pixel(pixel2,couleurchoisi);
			pixel2.x++ ;
		}

		xdroite = pixel2.x;
		//boucle, pour chaque maximal de gauche on va avancer sur la droite et on va monter et descendre d'un cran, cela va permettre de parcourir tout l'écran
		//cela permet de faire un appel maximal de fonction de la valeur y max (dans notre cas 800)
		//on ne peut oublier aucun pixel possible même avec des formes complexes
		//gif explicatif de l'algorithme dans le dossier du cpaint
	    for(pixel3.x=xgauche+1; pixel3.x<xdroite;pixel3.x++)
	    {
			if (pixel3.y>101)
			{
				pixel3.y = pixel.y;
				pixel3.y--;
				remplissage(pixel3);
			}

			if (pixel3.y<699)
			{
				pixel3.y = pixel.y;
				pixel3.y++;
				remplissage(pixel3);
			}
		}
	}
}

//fonction qui fais un calcul d'équation cartésienne de plan (float)
// prend trois points en arguments et renvoie le résultat de l'équation.

float calcul_de_plan(Point p1, Point p2, Point p3)
{
	return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
}


//fonction qui verifie si un point est dans un triangle (int bool)
//prend les trois points du triangles en argument et le point qu'on souhaite vérifier
//si les trois équations de plan sont inférieur OU si elle sont suppérieur à 0
//alors renvoie 1, sinon 0
int point_dans_triangle(Point t1, Point t2, Point t3, Point point)
{
	float z1 = calcul_de_plan(t1, t2, point);
	float z2 = calcul_de_plan(t2, t3, point);
	float z3 = calcul_de_plan(t3, t1, point);

	if ((z1 > 0 && z2 > 0 && z3 > 0) || (z1 < 0 && z2 < 0 && z3 < 0))
	    return 1;
	else
		return 0;
}

// Fonction qui permet d'aggrandir un trait, (void)
// Prend deux points en argument
// fait une boucle pour que pour chaque valeur x++ de y++ cela forme une nouvelle ligne
void trait_plus_gros(Point p1,Point p2)
{
	int j,k;
	Point p1trait, p2trait;
	p1trait = p1;
	p2trait = p2;
	for(j = 0 ; j < tailleoutil ; j++)
	{
		p1trait.x = p1.x;
		p2trait.x = p2.x;
		for(k = 0 ; k < tailleoutil ; k++)
		{
			if(verification_plateau(p1trait)&&verification_plateau(p2trait))
				dessiner_ligne(p1trait, p2trait, couleurchoisi);
			
			p1trait.x++;
			p2trait.x++;
		}
		p1trait.y++;
		p2trait.y++;
	}
}
// Fonction qui permet d'agrandir un cercle, (void)
// Prendre un point et un rayon en argument
// fais une boucle qui agrandit le cercle en augmentant son rayon de 1 à chaque fois
void cercle_plus_gros(Point centre, int rayon)
{
	int i;
	for(i = 0; i < tailleoutil; i++)
	{
		rayon++;
		
		dessiner_cercle(centre, rayon, couleurchoisi);
	}
}


//Fonction qui permet d'agrandir la gomme, (void)
// Prend deux points en argument
// fait une boucle pour que pour chaque valeur x++ de y++  et que pour chaque valeur x-- et y-- cela forme une nouvelle ligne
void gomme_plus_grosse(Point p1,Point p2)
{
	int j,k;
	Point p1trait, p2trait;
	p1trait = p1;
	p2trait = p2;
	for(j = 0 ; j < 5 ; j++)
	{
		p1trait.x = p1.x;
		p2trait.x = p2.x;
		for(k = 0 ; k < 5 ; k++)
		{
			if(verification_plateau(p1trait)&&verification_plateau(p2trait))
				dessiner_ligne(p1trait, p2trait, blanc);
			
			p1trait.x++;
			p2trait.x++;
		}
		p1trait.x = p1.x;
		p2trait.x = p2.x;
		for(k = 0 ; k < 5 ; k++)
		{
			if(verification_plateau(p1trait)&&verification_plateau(p2trait))
				dessiner_ligne(p1trait, p2trait, blanc);
			
			p1trait.x--;
			p2trait.x--;
		}
		p1trait.y++;
		p2trait.y++;
	}
	p1trait.y = p1.y;
	p2trait.y = p2.y;

	for(j = 0 ; j < 5 ; j++)
	{
		p1trait.x = p1.x;
		p2trait.x = p2.x;
		for(k = 0 ; k < 5 ; k++)
		{
			if(verification_plateau(p1trait)&&verification_plateau(p2trait))
				dessiner_ligne(p1trait, p2trait, blanc);
			
			p1trait.x++;
			p2trait.x++;
		}
		p1trait.x = p1.x;
		p2trait.x = p2.x;
		for(k = 0 ; k < 5 ; k++)
		{
			if(verification_plateau(p1trait)&&verification_plateau(p2trait))
				dessiner_ligne(p1trait, p2trait, blanc);
			
			p1trait.x--;
			p2trait.x--;
		}
		p1trait.y--;
		p2trait.y--;
	}
}
