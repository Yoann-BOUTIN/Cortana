#include "Square.h"

Square::Square(float x = -1.0f, float y = 1.0f,float side = 0.1f, 
				float red = 1.0f,float green = 1.0f, float blue = 1.0f) :
	posX_(x), posY_(y),side_(side),
	red_(red),green_(green), blue_(blue),
	cptClick_(0), forme_(Constants::EMPTY){}

Square::~Square(){}

/* 
 * DESSIN DES FORMES
 * Fonction qui dessine les croix et carrés
 */
void Square::draw()
{
	if (forme_ == Constants::CROIX)
	{
		GraphicPrimitives::drawLine2D(posX_ + (0.1*side_), posY_ + (0.1*side_), posX_ + (side_ / 1.3) + (0.1*side_), posY_ + (side_ / 1.3) + (0.1*side_), 1.0, 0.0, 0.0);
		GraphicPrimitives::drawLine2D(posX_ + (0.1*side_), posY_ + (side_ / 1.3) + (0.1*side_), posX_ + (side_ / 1.3) + (0.1*side_), posY_ + (0.1*side_), 1.0, 0.0, 0.0);
	}
	else if (forme_ == Constants::ROND){
		GraphicPrimitives::drawLine2D(posX_ + (0.1*side_), posY_ + (0.1*side_), posX_ + (0.9*side_), posY_ + (0.1*side_), 0.0, 1.0, 0.0);
		GraphicPrimitives::drawLine2D(posX_ + (0.1*side_), posY_ + (0.9*side_), posX_ + (0.9*side_), posY_ + (0.9*side_), 0.0, 1.0, 0.0);
		GraphicPrimitives::drawLine2D(posX_ + (0.1*side_), posY_ + (0.1*side_), posX_ + (0.1*side_), posY_ + (0.9*side_), 0.0, 1.0, 0.0);
		GraphicPrimitives::drawLine2D(posX_ + (0.9*side_), posY_ + (0.1*side_), posX_ + (0.9*side_), posY_ + (0.9*side_), 0.0, 1.0, 0.0);
	}
}
