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

public:
	MyGameEngine(Menu * menu, Morpion *morpion) :
	menu_(menu),morpion_(morpion){}

    virtual void idle();
};
