#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"
#include "Menu.h"

class MyGameEngine:public GameEngine {

private:
	Menu * menu_;
	Morpion *morpion_;
	std::vector<Player *> *player_;
	std::vector<IA *> *ia_;

public:
	MyGameEngine(Menu * menu, Morpion *morpion, std::vector<Player *> *player, std::vector<IA *> *ia) :
	menu_(menu),morpion_(morpion), player_(player),ia_(ia){}

    virtual void idle();
};
