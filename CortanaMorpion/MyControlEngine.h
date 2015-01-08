#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyControlEngine:public ControlEngine {

private:
	Morpion *morpion_;
	Player *player_;
	IA *ia_;
public:

	MyControlEngine(Morpion *morpion, Player *player, IA *ia) :
	morpion_(morpion),player_(player),ia_(ia){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
