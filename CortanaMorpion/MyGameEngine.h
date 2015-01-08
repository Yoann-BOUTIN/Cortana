#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyGameEngine:public GameEngine {

private:
	Morpion *morpion_;
	std::vector<Player *> players_;
	std::vector<IA *> ias_;

public:
	MyGameEngine(Morpion *morpion, std::vector<Player *> players, std::vector<IA *> ias) :
	morpion_(morpion), players_(players),ias_(ias){}
    virtual void idle();
    
};
