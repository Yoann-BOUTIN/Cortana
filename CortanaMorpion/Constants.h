#pragma once
namespace Constants
{
	// ABOUT WINDOW
	const int WINDOW_WIDTH		= 600; // largeur de la fenetre de jeu
	const int WINDOW_HEIGHT		= 600; // hauteur de la fenetre de jeu
	const int TAILLE_MORPION_3	= 3; // taille morpion 3x3
	const int TAILLE_MORPION_5	= 5; // taille morpion 5x5
	const int TAILLE_MORPION_10 = 10; // taille morpion 10x10

	//ABOUT PLAYER
	const int EMPTY			= -999; // pour les cases sans forme
	const int PLAYER		= -4; // identifiant d'un joueur
	const int PLAYER_TWO	= -3; // identifiant d'un joueur (dans le cas d'un morpion joueur contre joueur)
	const int ORDI			= -2; // identifiant d'un ordinateur
	const int ORDI_TWO		= -1; // identifiant d'un ordinateur (dans le cas d'un morpion ordinateur contre ordinateur
	const int ROND			= 0; // identifiant de la forme carre (cela devait etre des ronds a la base)
	const int CROIX			= 1; // identifiant de la forme croix
}