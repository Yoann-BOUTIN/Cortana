#pragma once
#include "IA.h"
#include <time.h>

class IARandom :
	public IA
{
public:
	IARandom(const int shape, Morpion *morpion);
	~IARandom();

	void calculIA(); // fonction qui va jouer sur des cases aleatoires
};

