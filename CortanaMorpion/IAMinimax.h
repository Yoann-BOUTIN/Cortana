#pragma once
#include "IA.h"
#include <time.h>

const int MINEVAL = -100000;
const int MAXEVAL = 100000;

class IAMinimax :
	public IA
{
public:
	IAMinimax(const int shape, Morpion * morpion);
	~IAMinimax();

	void calculIA(Morpion * morpion, int prof);
	int calcMin(Morpion *morpion, int prof);
	int calcMax(Morpion *morpion, int prof);
	int evalue(Morpion * morpion);
	int calcScore(int cntpion, int cntjoueur);
	int comptePions(Morpion *morpion);
	int getOtherShape(){ return (shape_ == Constants::CROIX) ? Constants::CROIX : Constants::ROND; }
};

