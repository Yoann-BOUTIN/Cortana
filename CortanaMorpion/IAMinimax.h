#pragma once
#include "IA.h"
#include <time.h>

const int MINEVAL = -10000000000;
const int MAXEVAL = 10000000000;

class IAMinimax :
	public IA
{
public:
	IAMinimax(const int shape, Morpion * morpion);
	~IAMinimax();

	void calculIA(int prof);
	int calcMin(Morpion *morpion, int prof);
	int calcMax(Morpion *morpion, int prof);
	int evalue(Morpion * morpion);
	int calcScore(int cntpion, int cntjoueur);
	int comptePions();
	int getOtherShape(){ return (shape_ == Constants::CROIX) ? Constants::CROIX : Constants::ROND; }
};

