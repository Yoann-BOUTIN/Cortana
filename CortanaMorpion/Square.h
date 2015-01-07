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
	
	int getCptClick(){ return cptClick_; }
	int getForme(){ return forme_; }

	void incCptClick(){ cptClick_++; }
	void draw();
	void setForme(const int forme){ forme_ = forme; };
	void restoreCptClick(){ cptClick_ = 0; }
	void setColor(float, float, float);
	void setCptClick(int i){ cptClick_ = i; }
	
	float getX(){ return posX_; }
	float getY(){ return posY_; }
	float getSide(){ return side_; }

	float getRed(){ return red_; }
	float getGreen(){ return green_; }
	float getBlue(){ return blue_; }
};