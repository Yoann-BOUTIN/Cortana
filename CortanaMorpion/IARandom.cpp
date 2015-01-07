#include "IARandom.h"


IARandom::IARandom(const int shape, Morpion *morpion)
{
	//INITIALISATION DE LA SEED POUR LE RANDOM
	srand(time(NULL));

	shape_ = shape;
	morpion_ = morpion;
	prof_ = 0;
	cptEval_ = 0;
}


IARandom::~IARandom()
{
}

void IARandom::calculIA(int prof)
{
	int i = 0;
	int j = 0;
	//ON CHERCHE ALEATOIREMENT UNE CASE NON JOUEE
	do
	{
		i = rand() % (*morpion_).getSize();
		j = rand() % (*morpion_).getSize();
	} while ((*morpion_).getSquare(i, j)->getCptClick() != 0);
	//CASE COCHEE ET CHANGEMENT DU JOUEUR COURANT
	(*morpion_).play(i, j, getShape());
}