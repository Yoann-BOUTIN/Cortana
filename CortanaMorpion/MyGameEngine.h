#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyGameEngine:public GameEngine {

private:
	Morpion *morpion_;
	Player *player_;
	IA * ia_;

public:
	MyGameEngine(Morpion *morpion, Player *player, IA *ia) :
	morpion_(morpion), player_(player),ia_(ia){}
    virtual void idle();
    
};
