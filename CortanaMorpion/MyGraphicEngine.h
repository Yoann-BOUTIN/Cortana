#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"

class MyGraphicEngine:public GraphicEngine {
   
private:
	Morpion *morpion_;
	Player *player_;
	IA *ia_;

public:
	MyGraphicEngine(Morpion *morpion, Player *player, IA *ia) :
	morpion_(morpion),player_(player),ia_(ia){}
    virtual void Draw();
};
