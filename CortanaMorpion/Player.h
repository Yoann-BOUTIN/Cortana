#pragma once
#include "GraphicPrimitives.h"

class Player
{
private:
	int shape_;

public:
	Player(const int shape);
	~Player();

	int getShape(){ return shape_; }

};