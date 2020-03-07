/*
 * couleur.c
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
#include "couleur.h"
#include "../lib/libgraphique.h"
#include "global.h"

//Fonction void de sélection de la couleur
//ne demande rien
//demande un point, fait les vérifications de la couleur et la donne 
void selection_couleur(Point clic)
{
	Point couleurchanger = {115, 60};
	if(verification_couleur(clic))
	{
		couleurchoisi = couleur_point(clic); 	
		dessiner_rectangle(couleurchanger,72,31, couleurchoisi);	
	}
	actualiser();

}
