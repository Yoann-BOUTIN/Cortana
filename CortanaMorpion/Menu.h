#pragma once
#include "Player.h"
#include "Square.h"
#include "IA.h"

class Menu
{
private:
	bool selectionsValidated_;
	std::vector< Player *> pl_;
	std::vector< IA *> ia_;

	std::vector<Square *> selectionTaille_;
	std::vector<Square *> selectionJ1_;
	std::vector<Square *> selectionJ2_;
	float red_;
	float green_;
	float blue_;
	bool gameReady_;
	int choixTaille_;
	int choixJ1_;
	int choixJ2_;
	Square *selectionValider_;

public:
	Menu();
	~Menu();

	Player * getPlayer(int i){ return pl_[i]; }
	IA * getIa(int i){ return ia_[i]; }

	bool isSelectionDone(){ return selectionsValidated_; }

	void draw();
	void clickTaille(Morpion *morpion, float posx, float posy);
	void clickJ1(float posx, float posy);
	void clickJ2(float posx, float posy);
	void clickValider(Morpion *morpion, float posx, float posy);
	void setColor(float f);
	bool getReady(){ return gameReady_; }
	void setReady(){ gameReady_ = true; }
	void incChoixTaille(){ choixTaille_ = 1; }
	void incChoixJ1(){ choixJ1_ = 1; }
	void incChoixJ2(){ choixJ2_ = 1; }
	bool choixOK(){ return ((choixTaille_ + choixJ1_ + choixJ2_) == 3); }
};

