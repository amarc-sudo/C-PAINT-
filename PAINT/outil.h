#ifndef __OUTIL__
#define __OUTIL__



#include "../lib/libgraphique.h"
#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"
#include "global.h"

//int dessin[HAUTEUR1 - HAUTEUR][LARGEUR1 - LARGEUR];

void taille(Point);

//Prend des points à l'aide du curseur de la souris et trace des traits à chaque fois 
void crayon(Point);

// Fonction qui agit comme le crayon mais qui repasse en blanc la où il y a un déplacement de souris
void gomme(Point);

void ligne();

//prend 3 points et trace des traits entre eux
void dessiner_triangle();

//prend 3 points puis trace des traits entre eux.Elle remplit le triangle en regardant 
//si les points sont dans le triangle à l'aide d'une équation cartésienne de plan
void dessiner_triangle_plein();


//demande 2 points, calcule les 2 autres points et remplit le rectangle avec une couleur
void rectangle();

//fonction pour dessiner le rectangle plein via n'importe qu'elle point
void dessiner_rectangle_par_coins (Point p1, Point p2);


// demande 2 points, calcule les 2 autres points
void rectanglevide();

//trace un rectangle vide. pour simplifier la fonction précédente
void tracer_rectangle_vide(Point p1, Point p2, Point p3, Point p4);

//demande des points à l'utilisateur et trace une ligne au bout de 2, 
//chaque nouveau clic rajoute un point qui est relié au dernier point avec un trait. Se stoppe avec un clic droit.
void polygonevide();

//demande des points à l'utilisateur, au bout de 3 clics trace un triangle plein (cf triangle plein), 
//chaque nouveau point trace un triangle à l'aide des deux dernier points
void polygone_plein();

//demande 2 points, calcule le centre et trace un cercle de diamètre des 2 points
void cercle();

// demande 2 points, calcule le centre et trace un cercle de diamètre des 2 points et le remplit
void disque();

//prend la couleur d'un point donnée
void pipette();

//permet d'insérer une image à tout moment. Ne pas oublier le .bmp à la fin du nom pour l'insérer
void afficher_image_choisi();

// remplit ce qu'on sélectionne de la couleur choisit. La fonction colorie les pixels
// qui sont à coté de d'eux jusqu'à atteindre la limite (trait ou limite de zone de dessin)
//AVEC BOUCLE ET RECURSIVITE // SANS CRASH OVERFLOW
void remplissage(Point);

//prend l'image de la zone de texte et la met dans un tableau. Puis demande un nom de fichier qui
//doit finir par .bmp. envoie ensuite ce tableau une fonction de la libgraphique qui va crée une surface
//et mettre ce tableau dans cette surface. puis convertir cette surface en image bmp
void sauvegarder(int dessin[LARGEURTABLEAU][HAUTEURTABLEAU]);

void und(int dessin[LARGEURTABLEAU][HAUTEURTABLEAU]);

//fait une équation cartésienne de plan entre 3 point
float calcul_de_plan(Point p1, Point p2, Point p3);
//verifie via une verification. si les trois verifcation sont positif OU negatif alors le point est dans
//le triangle et on renvoie un Bool
int point_dans_triangle(Point t1, Point t2, Point t3, Point point);

//produit plusieurs trait via une boucle. dépend de la tailleoutil
void trait_plus_gros(Point, Point);
//produit plusieurs cercle pour grossir le cercle de base. dépend de la tailleoutil
void cercle_plus_gros(Point centre, int rayon);
//fonction qui permet de faire une gomme beaucoup plus grosses
void gomme_plus_grosse(Point p1,Point p2);
#endif
