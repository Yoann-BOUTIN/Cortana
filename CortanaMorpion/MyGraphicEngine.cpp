#include "MyGraphicEngine.h"

void MyGraphicEngine::Draw()
{
	//CROIX GAGNE
	if ((*morpion_).getCroixWin()){
		GraphicPrimitives::drawText2D("Le joueur 1 gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
	}
	//ROND GAGNE
	else if ((*morpion_).getRondWin()){
		GraphicPrimitives::drawText2D("Le joueur 2 gagne !", -0.175f, 0.9f, 1.0f, 1.0f, 1.0f);
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
