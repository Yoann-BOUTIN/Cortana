#pragma once
#include "IA.h"
#include <time.h>

class IARandom :
	public IA
{
public:
	IARandom(const int shape, Morpion *morpion);
	~IARandom();

	void calculIA(int prof);
};

