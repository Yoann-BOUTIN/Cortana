#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyGraphicEngine:public GraphicEngine {
   // Classe qui gère la partie graphique
private:
	Morpion *morpion_;
	std::vector<Player *> players_;
	std::vector<IA *> ias_;

public:
	MyGraphicEngine(Morpion *morpion, std::vector<Player *> players, std::vector<IA *> ias) :
	morpion_(morpion),players_(players),ias_(ias){}
    virtual void Draw();
};
