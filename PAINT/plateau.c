
#include "plateau.h"
//fonction de création du plateau
void plateau()
{
	Point c = {0,0};
	ouvrir_fenetre(RESV,RESH, LARGEURTABLEAU, HAUTEURTABLEAU, POSX, POSY);
	SDL_WM_SetCaption("C-PAINT !", NULL);
	SDL_Surface*    icon;

	icon = SDL_LoadBMP("image/ico.bmp");
	if (icon != 0)
        SDL_WM_SetIcon(icon, NULL);
	//on affiche le plateau
	afficher_image("image/c_paint.bmp", c);
	afficherinstruction("Bienvenue, choisissez une couleur puis un outil pour commencer a dessiner", 15);
	indication_taille();
}
//fonction void
//prend en argument char qui est le nom de l'image
//vérifie si elle existe. si non fait une backup et ferme le programme
//si oui on affiche l'image
void plateau_img(char * image)
{
	Point c = {0,0},coin_image = {201,101};
	FILE *f=fopen(image,"r");
    if(!f)
        {
        fprintf(stderr,"Erreur: le chemin '%s' ne mene a aucune image valable pour etre ouverte\n",image);
        exit(1);
        }
    fclose(f);

	ouvrir_fenetre(RESV,RESH, LARGEURTABLEAU, HAUTEURTABLEAU, POSX, POSY);
	SDL_WM_SetCaption("C-PAINT !", NULL);
	SDL_Surface*    icon;

	icon = SDL_LoadBMP("image/ico.bmp");
	if (icon != 0)
    SDL_WM_SetIcon(icon, NULL);
	//on affiche le plateau

	afficher_image("image/c_paint.bmp", c);
	afficher_image(image,coin_image);
	afficherinstruction("Bienvenue, choisissez une couleur puis un outil pour commencer a dessiner", 15);
	indication_taille();
}
//fonction int bool qui prend un point en argument
//renvoie 1 si le point est dans le plateau(zone de dessin) sinon 0
int verification_plateau(Point p1)
{
	if(p1.x > LARGEUR && p1.x < RESV && p1.y >HAUTEUR && p1.y < RESH)
		return 1;
	else
		return 0;

}

//fonction int bool qui prend un point en argument
//renvoie 1 si le point est dans la pallete de couleur si non 0
int verification_couleur(Point p1)
{
	if((p1.x > 100 && p1.x < 200 && p1.y > 100 && p1.y < 450)||(p1.x > 50 && p1.x < 200 && p1.y > 446 && p1.y < 600))
		return 1;
	else
		return 0;
}


//fonction int bool qui prend un point en argument
//renvoie 1 si le point est dans la pallete de taille si non 0
int verification_taille(Point p1)
{
	if(p1.x > 0 && p1.x < 50 && p1.y > 400 && p1.y < 600)
		return 1;
	else
		return 0;
}

//fonction void qui prend une taille de texte et le texte en argument
//affiche le texte a l'endroit prévue pour
void afficherinstruction(char *instruction, int taille)
{
	Point coin = {250,0};
	dessiner_rectangle(coin, 750,52, noir);
	afficher_texte(instruction, taille, coin, blanc);
	actualiser();
}
//fonction void qui prend un texte en argument
//affiche le texte a l'endroit prévue pour
void afficher_outil_selectioner(char *instruction)
{
	Point coin = {252,52};
	dessiner_rectangle(coin, 750,49, gris);
	afficher_texte(instruction, 40, coin, blanc);
	actualiser();
}

//fonction void qui prend un point en argument
//change la taille de l'outil selon ou est situé le texte.
void changement_taille(Point p1)
{
	if (p1.x > 0 && p1.x < 50 && p1.y > 400 && p1.y < 450)
		tailleoutil = 1;
	if(p1.x > 0 && p1.x < 50 && p1.y > 450 && p1.y < 500)
		tailleoutil = 2;
  	if(p1.x > 0 && p1.x < 50 && p1.y > 500 && p1.y < 550)
		tailleoutil = 4;
	if(p1.x > 0 && p1.x < 50 && p1.y > 550 && p1.y < 600)
		tailleoutil = 6;
	indication_taille();
}
//fonction void qui prend deux point en argument
//augmente la taille de l'indication du trait en fonction de la tailleoutil
void trait_plus_gros_noir(Point p1,Point p2)
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
				dessiner_ligne(p1trait, p2trait, noir);
			
			p1trait.x++;
			p2trait.x++;
		}
		p1trait.y++;
		p2trait.y++;
	}
}

void indication_taille()
{
	Point coin = {202,52}, outil_endroit_1 = {207,75},outil_endroit_2 = {240,75};
	dessiner_rectangle(coin,47,47,gris);
	dessiner_ligne(outil_endroit_1, outil_endroit_2, noir);
	trait_plus_gros_noir(outil_endroit_1, outil_endroit_2);
	actualiser();
}
