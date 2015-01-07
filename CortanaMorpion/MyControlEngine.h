#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"
#include "Menu.h"

class MyControlEngine:public ControlEngine {

private:
	Menu *menu_;
	Morpion *morpion_;
	std::vector<Player *> *player_;
	std::vector<IA *> *ia_;
public:

	MyControlEngine(Menu * menu, Morpion *morpion, std::vector<Player *> * player, std::vector<IA *> * ia) :
	menu_(menu), morpion_(morpion),player_(player),ia_(ia){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
