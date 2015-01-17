#pragma once
#include "GraphicPrimitives.h"
#include "Constants.h"
class Square
{

private:
	int cptClick_;
	int forme_;

	float posX_, posY_;
	float side_;
	float red_, green_, blue_;

public:
	Square(	float x, float y, float side,
			float red, float green, float blue);
	~Square();
	
	int getCptClick(){ return cptClick_; } // fonction permettant de savoir si une case est deja utilise ou non
	int getForme(){ return forme_; } //  fonction permettant de savoir quelle forme est sur la case

	void incCptClick(){ cptClick_++; } // incremente le compteur d'utilisation de la case
	void draw(); // dessine une case
	void setForme(const int forme){ forme_ = forme; }; // modifie la forme de la case
	void restoreCptClick(){ cptClick_ = 0; } //  reinitialise le compteur d'utilisation de la case
	
	float getX(){ return posX_; } // renvoi la coordonnee x de la case
	float getY(){ return posY_; } // renvoi la coordonnee y de la case
	float getSide(){ return side_; } // renvoi la taille (taille d'un cote) de la case 
};