#pragma once
#include "Engine.h"
#include "GraphicPrimitives.h"
#include "Morpion.h"
#include "Player.h"
#include "IA.h"
#include "Menu.h"

class MyGraphicEngine:public GraphicEngine {
   
private:
	Menu * menu_;
	Morpion *morpion_;

public:
	MyGraphicEngine(Menu * menu, Morpion *morpion) :
	menu_(menu), morpion_(morpion){}

    virtual void Draw();
};
