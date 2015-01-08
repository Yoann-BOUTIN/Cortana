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
public:

	MyControlEngine(Menu * menu, Morpion *morpion) :
	menu_(menu), morpion_(morpion){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
