#include <iostream>
#include <cstdlib>

#include "Engine.h"
#include "MyGraphicEngine.h"
#include "MyGameEngine.h"
#include "MyControlEngine.h"
#include "Morpion.h"
#include "Constants.h"
#include "Player.h"
#include "IARandom.h"
#include "IAMinimax.h"
#include "IAAlphaBeta.h"
#include <time.h>

int main(int argc, char * argv[])
{
	Engine e(argc, argv, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Cortana");
	bool notReady = true; // booleen a true de base, et sera mis a false lorsque la configuration de la partie aura ete realisee
	int taille; // taille de la grille du morpion
	int player1, player2; //identificateur des deux joueurs
	std::vector<Player *> players_; // vecteur de joueurs
	std::vector<IA *> ias_; // vecteur d'ordinateurs

	GraphicEngine * ge;
	GameEngine * gme;
	ControlEngine * ce;

	// tant que la configuration n'est pas terminee le jeu ne se lance pas
	while (notReady)
	{
		std::cout << "#################################" << std::endl;
		std::cout << "# Bienvenu dans Cortana morpion #" << std::endl;
		std::cout << "#################################" << std::endl;

		std::cout << "Veuillez choisir la taille du morpion :  3 pour (3x3), 5 pour (5x5), 10 pour (10x10)" << std::endl;
		std::cin >> taille;
		
		std::cout << "Veuillez choisir le joueur 1: 0 <-> Humain, 1 <-> Random, 2 <-> MinMax, 3 <-> AlphaBeta" << std::endl;
		std::cin >> player1;

		std::cout << "Veuillez choisir le joueur 2: 0 <-> Humain, 1 <-> Random, 2 <-> MinMax, 3 <-> AlphaBeta" << std::endl;
		std::cin >> player2;
		notReady = false;
	}
	// creation d'un morpion selon la taille choisi par l'utilisateur
	Morpion * morpion_;
	switch (taille)
	{
	case 3:
		morpion_ = new Morpion(Constants::TAILLE_MORPION_3);
		break;
	case 5:
		morpion_ = new Morpion(Constants::TAILLE_MORPION_5);
		break;
	case 10:
		morpion_ = new Morpion(Constants::TAILLE_MORPION_10);
		break;
	default:
		morpion_ = new Morpion(Constants::TAILLE_MORPION_3);
		break;
	}
	//CREATION DU MORPION
	(*morpion_).init();
	//CREATION D UNE INSTANCE PLAYER
	switch (player1)
	{
	case 0:
		players_.push_back(new Player(Constants::CROIX));
		//INITIALISATION DU JOUEUR COURANT
		(*morpion_).setCurrentPlayer(Constants::PLAYER, Constants::CROIX);
		break;
	case 1:
		ias_.push_back(new IARandom(Constants::CROIX, morpion_));
		//INITIALISATION DU JOUEUR COURANT
		(*morpion_).setCurrentPlayer(Constants::ORDI, Constants::CROIX);
		break;
	case 2:
		ias_.push_back(new IAMinimax(Constants::CROIX, morpion_));
		//INITIALISATION DU JOUEUR COURANT
		(*morpion_).setCurrentPlayer(Constants::ORDI, Constants::CROIX);
		break;
	case 3:
		ias_.push_back(new IAAlphaBeta(Constants::CROIX, morpion_));
		//INITIALISATION DU JOUEUR COURANT
		(*morpion_).setCurrentPlayer(Constants::ORDI, Constants::CROIX);
		break;
	default:
		players_.push_back(new Player(Constants::CROIX));
		//INITIALISATION DU JOUEUR COURANT
		(*morpion_).setCurrentPlayer(Constants::PLAYER, Constants::CROIX);
		break;
	}
	//CREATION D UNE INSTANCE IA
	switch (player2)
	{
	case 0:
			players_.push_back(new Player(Constants::ROND));
	case 1:
		ias_.push_back(new IARandom(Constants::ROND, morpion_));
		break;
	case 2:
		ias_.push_back(new IAMinimax(Constants::ROND, morpion_));
		break;
	default:
		ias_.push_back(new IAAlphaBeta(Constants::ROND, morpion_));
		break;
	}

	(*morpion_).setPlayers(players_);

	ge = new MyGraphicEngine(morpion_, players_, ias_);
	gme = new MyGameEngine(morpion_, players_, ias_);
	ce = new MyControlEngine(morpion_, players_, ias_);

	e.setGraphicEngine(ge);
	e.setGameEngine(gme);
	e.setControlEngine(ce);

	e.start();
	return 0;
}