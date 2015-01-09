#pragma once
#include "IA.h"
#include <time.h>

const int MINEVAL = -100000;
const int MAXEVAL = 100000;

class IAMinimax :
	public IA
{
private:
	int ordi_;
public:
	IAMinimax(const int shape, Morpion * morpion);
	~IAMinimax();

	void calculIA();
	int calcMin(int prof);
	int calcMax(int prof);
	int evalue();
	int calcScore(int cntpion, int cntjoueur);
	int comptePions();
	int getOtherShape(){ return (shape_ == Constants::CROIX) ? Constants::CROIX : Constants::ROND; }

	int verifLigne(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifColonne(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifDiagG(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifDiagD(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
};

