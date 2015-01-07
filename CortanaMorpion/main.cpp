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
#include "Menu.h"

int main(int argc, char * argv[])
{
	Engine e(argc, argv, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Cortana");

	Menu menu;
	//CREATION DU MORPION
	Morpion *morpion_ = nullptr;
	//CREATION D UNE INSTANCE PLAYER
	std::vector<Player *> players_;
	//CREATION D UNE INSTANCE IA
	std::vector<IA *> ias_;

	GraphicEngine * ge = new MyGraphicEngine(&menu, morpion_,&players_,&ias_);
	GameEngine * gme = new MyGameEngine(&menu, morpion_, &players_, &ias_);
	ControlEngine * ce = new MyControlEngine(&menu, morpion_, &players_, &ias_);
	
	e.setGraphicEngine(ge);
	e.setGameEngine(gme);
	e.setControlEngine(ce);

	e.start();
	return 0;
}