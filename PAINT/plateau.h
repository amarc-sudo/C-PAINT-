#ifndef __PLATEAU__
#define __PLATEAU__
#include "../lib/libgraphique.h"
#include "global.h"
#include "outil.h"
#define  gris_plateau 808080

#define LARGEUR 200
#define HAUTEUR 100

// Fonction qui affiche la zone de dessin avec les icones
void plateau();

// Fonction qui affiche la zone de dessin avec les icones et une image choisit
void plateau_img(char * image);

// Fonction de vérification qui permet de savoir si les clics de l'utilisateur sont dans la zone de dessin
int verification_plateau(Point);

// Fonction de vérification qui permet de savoir si on a cliqué dans la palette de couleur
int verification_couleur(Point);

// Fonction de vérification qui permet de savoir si on a cliqué dans la palette de taille
int verification_taille(Point p1);

// Fonction qui change l'épaisseur réalisée par l'outil en fonction du clic sur la taille que l'on souhaite.
void changement_taille(Point p1);

// Fonction qui affiche des instructions prédéfinies pour aider l'utilisateur avec les outils
void afficherinstruction(char *instruction, int);

// Fonction qui affiche l'outil selectionné
void afficher_outil_selectioner(char *outil);

// Fonction pour afficher la taille de l'outil
void trait_plus_gros_noir(Point p1,Point p2);

void indication_taille();

#endif
