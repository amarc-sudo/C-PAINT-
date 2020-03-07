/****************************************************************
*				 Projet C_Paint									/
*				 Par Romuald Hanriot et							/
*				 Aurélien Marc									/
*																/	
****************************************************************/

#include "lettre.h"
#include "couleur.h"
#include "plateau.h"
#include "outil.h"
#include "global.h"
#include <math.h>
#include <string.h>
#include "menu.h"
#include <time.h>

//main. plusieurs variable. des points pour afficher des images et faire des vérifications.
//lance la fonction menu en premier qui laisse demande un choix puis lance le paint
//ensuite, tant qu'on n'a pas quitter ou appuyer sur exit
//demande un clic pour choisir un des principaux outils ou un changement de couleur ou de taille.
int main(void)
{

	Point p, pixel, verification, coinduplateau={201,101};
	int fonctionnement = 1;
	char enregistrementimage[100];
	tailleoutil = 1;
	menu();
	sauvegarder(enregistrement);
	actualiser();
	while(fonctionnement)
	{
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////Barre des outils////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
		traiter_evenements();
		p = clic_a_eu_lieu();
		
		////////////////////////////
		//verification de couleurs//
		////////////////////////////
		if (verification_couleur(p))
			selection_couleur(p);
 		
 		//////////////////////////////////
 		//verification de taille d'outil//
 		//////////////////////////////////
 		else if (verification_taille(p))
			changement_taille(p);


		
		////////
		//texte
		////////
		else if ((p.x > 0 && p.x < 50)&& (p.y > 50 && p.y < 100))
		{
			sauvegarder(enregistrement);
			afficherinstruction("Selectionnez l'endroit et ecrivez, appuyer sur ctrl pour finir",20);
			afficher_outil_selectioner("texte");
			lettre(attendre_clic(),(10*tailleoutil));
			afficher_outil_selectioner(" ");
		}

		////////
		//gomme
		////////
		else if ((p.x > 50 && p.x < 100)&& (p.y > 50 && p.y < 100))
		{
			sauvegarder(enregistrement);
			afficherinstruction("Cliquez une fois pour gommer et clic droit pour arrêter",20);
			afficher_outil_selectioner("gomme");
			gomme(verification);
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		//////////////
		//crayon
		/////////////
		else if ((p.x > 50 && p.x < 99) && (p.y > 300 && p.y < 350))
		{
			sauvegarder(enregistrement);
			afficherinstruction("Selectionnez l'endroit ou commencer a ecrire ou changer la taille/couleur", 20);
			afficher_outil_selectioner("crayon");
			crayon(verification);
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		///////////////
		//triangle VIDE
		///////////////
		else if ((p.x > 50 && p.x < 100) && (p.y > 150 && p.y < 200))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 3 fois pour faire un triangle",20);
			afficher_outil_selectioner("triangle vide");
			dessiner_triangle();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		/////////////////
		//triangle plein
		/////////////////
		else if ((p.x > 50 && p.x < 100) && (p.y > 100 && p.y < 150))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 3 fois pour faire un triangle plein",20);
			afficher_outil_selectioner("triangle plein");
			dessiner_triangle_plein();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		///////////
		//rectangle
		///////////
		else if ((p.x > 0 && p.x < 50) && (p.y > 200 && p.y < 250))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 2 fois pour faire un rectangle", 20);
			afficher_outil_selectioner("rectangle plein");
			rectangle();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		
		////////////////
		//rectangle vide
		////////////////
		else if ((p.x > 0 && p.x < 50) && (p.y > 250 && p.y < 300))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 2 fois pour faire un rectangle vide", 20);
			afficher_outil_selectioner("rectangle vide");
			rectanglevide();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		//////////////////////
		//polygone non remplit
		//////////////////////
		else if ((p.x > 50 && p.x < 100) && (p.y > 250 && p.y < 300))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez pour faire des points et faites un clic droit pour stopper",20);
			afficher_outil_selectioner("polygone vide");
			polygonevide();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		//////////////////
		//polygone remplit
		/////////////////
		else if ((p.x > 50 && p.x < 100) && (p.y > 200 && p.y < 250))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez pour faire des points et faites un clic droit pour stopper",20);
			afficher_outil_selectioner("polygone plein");
			polygone_plein();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		////////
		//ligne
		////////
		else if ((p.x > 0 && p.x < 50) && (p.y >300 && p.y < 350))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 2 fois pour faire une ligne",20);
			afficher_outil_selectioner("ligne");
			ligne();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		/////////
		//disque
		/////////
		else if ((p.x > 0 && p.x < 50)&& (p.y > 100 && p.y < 150))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 2 fois pour faire un disque",20);
			afficher_outil_selectioner("cercle plein");
			disque();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}

		//cercle
		else if ((p.x > 0 && p.x < 50)&& (p.y > 150 && p.y < 200))
		{
			sauvegarder(enregistrement);
			afficherinstruction("cliquez 2 fois pour faire un cercle",20);
			afficher_outil_selectioner("cercle vide");
			cercle();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}

		/////////////////
		//remplisage
		/////////////////
		else if ((p.x > 50 && p.x < 99) && (p.y > 350 && p.y < 400))
		{
			sauvegarder(enregistrement);
			afficherinstruction("Selectionnez une couleur puis cliquez sur une figure pour la remplir avec la couleur voulue",20);
			afficher_outil_selectioner("pot de peinture");
			pixel = attendre_clic();
			if(verification_plateau(pixel))
			{
				couleuractuelle = couleur_point(pixel);
				remplissage(pixel);
				afficher_outil_selectioner(" ");
				afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
			}
		}

		//////////
		//pipette
		//////////
		else if ((p.x > 0 && p.x < 50) && (p.y > 350 && p.y < 400))
		{
			afficherinstruction("Cliquez sur une couleur pour la récuperer",20);
			pipette();
			afficher_outil_selectioner(" ");
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}	

		////////////////////
		//charger une image
		////////////////////
		else if ((p.x > 50 && p.x < 100) && (p.y > 400 && p.y < 445))
		{
			afficherinstruction("rentrez le nom de l'image que vous voulez charger", 20);
			sauvegarder(enregistrement);
			afficher_image_choisi();
			afficherinstruction("choisissez un outil, une couleur ou bien une taille.",20);
		}
		


		///////////////////////////////
		//sauvegarde de la création
		///////////////////////////////
		else if(p.x > 50 && p.x < 100 && p.y > 0 && p.y < 50)
		{
			sauvegarder(enregistrement);
			afficherinstruction("rentrez le nom de votre creation ! (il doit se finir par.bmp)", 20);
			scanf("%s",enregistrementimage);
			enregistre_bmp(enregistrement, enregistrementimage);
		}
		////////////////////////////////
		//retour en arrière
		/////////////////////////////////
		else if(p.x > 100 && p.x < 150 && p.y > 0 && p.y < 50)
			und(enregistrement);
		//////////////////////////////////
		//clear
		//////////////////////////////////
		else if(p.x > 150 && p.x < 250 && p.y > 0 && p.y < 50)
			dessiner_rectangle(coinduplateau, 800,600, blanc);

		//////////////
		//bouton exit
		//////////////
		else if(p.x > 0 && p.x < 50 && p.y > 0 && p.y < 50)
			fonctionnement = 0;
		actualiser();
	}
	fermer_fenetre();
	return 0;
}
