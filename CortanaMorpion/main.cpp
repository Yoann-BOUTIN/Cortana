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
#include <time.h>

int main(int argc, char * argv[])
{
	Engine e(argc, argv, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Cortana");
	bool notReady = true;
	int taille;
	int player1, player2;

	GraphicEngine * ge;
	GameEngine * gme;
	ControlEngine * ce;

	while (notReady)
	{
		std::cout << "#################################" << std::endl;
		std::cout << "# Bienvenu dans Cortana morpion #" << std::endl;
		std::cout << "#################################" << std::endl;

		std::cout << "Veuillez choisir la taille du morpion :  3 pour (3x3), 5 pour (5x5), 10 pour (10x10) ?" << std::endl;
		std::cin >> taille;
		
		std::cout << "Veuillez le joueur 1: 0 pour Humain, 1 pour Random, 2 pour MinMax, 3 pour AlphaBeta ?" << std::endl;
		std::cin >> player1;

		std::cout << "Veuillez le joueur 2: 0 pour Humain, 1 pour Random, 2 pour MinMax, 3 pour AlphaBeta ?" << std::endl;
		std::cin >> player2;
		notReady = false;
	}
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
	//INITIALISATION DU JOUEUR COURANT
	(*morpion_).setCurrentPlayer(Constants::PLAYER, Constants::CROIX);
	//CREATION D UNE INSTANCE PLAYER
	Player * player_;
	switch (player1)
	{
	case 0:
		player_ = new Player(Constants::CROIX);
		break;
	default:
		player_ = new Player(Constants::CROIX);
		break;
	}
	IA * ia_;
	//CREATION D UNE INSTANCE IA
	switch (player2)
	{
	case 1:
		ia_ = new IARandom(Constants::ROND, morpion_);
		break;
	case 2:
		ia_ = new IAMinimax(Constants::ROND, morpion_);
		break;
	default:
		ia_ = new IAMinimax(Constants::ROND, morpion_);
		break;
	}
	ge = new MyGraphicEngine(morpion_, player_, ia_);
	gme = new MyGameEngine(morpion_, player_, ia_);
	ce = new MyControlEngine(morpion_, player_, ia_);

	e.setGraphicEngine(ge);
	e.setGameEngine(gme);
	e.setControlEngine(ce);

	e.start();
	return 0;
}