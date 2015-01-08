#include "MyGameEngine.h"


void MyGameEngine::idle()
{
	//VERIFIE S'IL Y A UN VAINQUEUR
	(*morpion_).endGame();
	//SINON L ORDI JOUE
	if ((*morpion_).getCurrentPlayer() == Constants::ORDI && !(*morpion_).getEndGame())
	{
		(*ia_).calculIA((*ia_).getProf());
	}
}