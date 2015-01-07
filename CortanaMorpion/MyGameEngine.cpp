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
			(*ia_)[0]->calculIA((*ia_)[0]->getProf());
			(*ia_)[0]->decProf();
		}
	}
}