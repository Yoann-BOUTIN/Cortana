#include "MyGraphicEngine.h"

void MyGraphicEngine::Draw()
{
	if ((*menu_).isSelectionDone())
	{
		//CROIX GAGNE
		if ((*morpion_).getCroixWin()){
			//LE JOUEUR A LES CROIX
			if ((*player_)[0]->getShape() == Constants::CROIX)
				GraphicPrimitives::drawText2D("Le joueur gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
			//L ORDI A LES CROIX
			else
				GraphicPrimitives::drawText2D("L'ordinateur gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
		}
		//ROND GAGNE
		else if ((*morpion_).getRondWin()){
			//LE JOUEUR A LES RONDS
			if ((*player_)[0]->getShape() == Constants::ROND)
				GraphicPrimitives::drawText2D("Le joueur gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
			//L ORDI A LES RONDS
			else
				GraphicPrimitives::drawText2D("L'ordinateur gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
		}
		// MATCH NUL
		else if ((*morpion_).isFull()){
			GraphicPrimitives::drawText2D("Match nul !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
		}
		// TRACE DES LIGNES
		for (int i = 0; i < morpion_->getSize(); i++)
		{
			float x = (*morpion_).getSquare(i, 0)->getX();
			float y = (*morpion_).getSquare(i, 0)->getY();

			GraphicPrimitives::drawLine2D(x, y, x + ((*morpion_).getSize()*(*morpion_).getSquareSize()), y, 1.0f, 1.0f, 1.0f);
			if (i + 1 == morpion_->getSize())
			{
				y = (*morpion_).getSquare(i, 0)->getY() + (*morpion_).getSquareSize();
				GraphicPrimitives::drawLine2D(x, y, x + ((*morpion_).getSize()*(*morpion_).getSquareSize()), y, 1.0f, 1.0f, 1.0f);
			}
		}
		// TRACE DES LIGNES
		for (int i = 0; i < morpion_->getSize(); i++)
		{
			float x = (*morpion_).getSquare(0, i)->getX();
			float y = (*morpion_).getSquare(0, i)->getY();

			GraphicPrimitives::drawLine2D(x, y, x, y + ((*morpion_).getSize()*(*morpion_).getSquareSize()), 1.0f, 1.0f, 1.0f);
			GraphicPrimitives::drawLine2D(x, y, x + ((*morpion_).getSize()*(*morpion_).getSquareSize()), y, 1.0f, 1.0f, 1.0f);
			if (i + 1 == morpion_->getSize())
			{
				x = (*morpion_).getSquare(0, i)->getX() + (*morpion_).getSquareSize();
				GraphicPrimitives::drawLine2D(x, y, x, y + ((*morpion_).getSize()*(*morpion_).getSquareSize()), 1.0f, 1.0f, 1.0f);
			}
		}
		// DESSIN DES CARRES DE JEUX
		for (int i = 0; i < morpion_->getSize(); i++)
		{
			for (int j = 0; j < morpion_->getSize(); j++)
			{
				(*morpion_).getSquare(i, j)->draw();
			}
		}

	}
	else
	{
		(*menu_).draw();
	}
}
