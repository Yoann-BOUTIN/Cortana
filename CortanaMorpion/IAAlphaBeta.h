#pragma once
#include "IA.h"
class IAAlphaBeta :
	public IA
{
private:
	int ordi_;

public:
	IAAlphaBeta(const int shape, Morpion * morpion);
	~IAAlphaBeta();


	void calculIA();
	int calcMin(int prof, int alpha, int beta);
	int calcMax(int prof, int alpha, int beta);
	int evalue();
	int calcScore(int cntpion, int cntjoueur);
	int comptePions();
	int getOtherShape(){ return (shape_ == Constants::CROIX) ? Constants::CROIX : Constants::ROND; }

	int verifLigne(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifColonne(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifDiagG(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
	int verifDiagD(Morpion *morpion, int shape, int nbVerif, int nbDecallage);
};

