#pragma once
#include "Player.h"
#include "Square.h"
#include "IA.h"
#include "IARandom.h"
#include "IAMinimax.h"

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
	bool taille_;
	bool J1_;
	bool J2_;
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
	int getChoixTaille(){ return choixTaille_; }
	int getChoixJ1(){ return choixJ1_; }
	int getChoixJ2(){ return choixJ2_; }
	void setChoixTaille(int n){ choixTaille_ = n; }
	void setChoixJ1(int n){ choixJ1_ = n; }
	void setChoixJ2(int n){ choixJ2_ = n; }
	bool choixOK(){ return ((choixTaille_ + choixJ1_ + choixJ2_) == 3); }
};

