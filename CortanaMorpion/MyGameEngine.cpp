#include "MyGameEngine.h"


void MyGameEngine::idle()
{
	if ((*menu_).isSelectionDone())
	{
		//VERIFIE S'IL Y A UN VAINQUEUR
		(*morpion_).endGame();
		//SINON L ORDI JOUE
		if ((*morpion_).getCurrentPlayer() == Constants::ORDI && !(*morpion_).getEndGame())
		{
			(*morpion_).getIA(0)->calculIA((*morpion_).getIA(0)->getProf());
			(*morpion_).getIA(0)->decProf();
		}
		else if ((*morpion_).getCurrentPlayer() == Constants::ORDI_TWO && !(*morpion_).getEndGame()){
			(*morpion_).getIA(1)->calculIA((*morpion_).getIA(1)->getProf());
			(*morpion_).getIA(1)->decProf();
		}
	}
}