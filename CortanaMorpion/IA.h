#pragma once
#include "Morpion.h"
#include <time.h>
const int MINEVAL = -100000;
const int MAXEVAL = 100000;
class IA
{
	// Classe mere des IA
protected:
	int shape_;
	int prof_;
	int cptEval_;
	Morpion *morpion_;

public:
	IA();
	~IA();

	int getShape(){ return shape_;} // fonction qui donne la forme du symbole correspondant à l'IA (un int)
	Morpion* getMorpion(){ return morpion_; } // fonction pour obtenir la grille de jeu
	virtual void calculIA() = 0; // fonction qui permet le lancement de la recherche du coup à jouer pour l'IA

	int getProf(){ return prof_; } // fonction permettant d'obtenir la profondeur
	void decProf(){ prof_--; } // decremente la profondeur
	void incProf(){ prof_++; } // incremente la profondeur

};

