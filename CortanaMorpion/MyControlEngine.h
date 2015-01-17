#pragma once
#include "Engine.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyControlEngine:public ControlEngine {
	// Classe qui va gerer les cliques.
private:
	Morpion *morpion_;
	std::vector<Player *> players_;
	std::vector<IA *> ias_;
public:

	MyControlEngine(Morpion *morpion, std::vector<Player *> players, std::vector<IA *> ias) :
	morpion_(morpion),players_(players),ias_(ias){}
    
    virtual void MouseCallback(int button, int state, int x, int y) ;
};
