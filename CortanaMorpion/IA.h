#pragma once
#include "Morpion.h"
#include <time.h>
const int MINEVAL = -100000;
const int MAXEVAL = 100000;
class IA
{
protected:
	int shape_;
	int prof_;
	int cptEval_;
	Morpion *morpion_;

public:
	IA();
	~IA();

	int getShape(){ return shape_;}
	Morpion* getMorpion(){ return morpion_; }
	virtual void calculIA() = 0;

	int getProf(){ return prof_; }
	void decProf(){ prof_--; }
	void incProf(){ prof_++; }

};

