#include "Menu.h"

Menu::Menu()
{
	setColor(0.1f);
	for (int i = 0; i < 4; i++){
		selectionTaille_.emplace_back(new Square(-0.475f + (i / 4.0f), 0.3f, 0.2f, 0.1f, 0.1f, 0.1f));
	}
	for (int i = 0; i < 4; i++){
		selectionJ1_.emplace_back(new Square(-0.7f + (i / 2.0f), 0.0f, 0.4f, 0.1f, 0.1f, 0.1f));
	}
	for (int i = 0; i < 3; i++){
		selectionJ2_.emplace_back(new Square(-0.7f + (i / 2.0f), -0.3f, 0.4f, 0.1, 0.1f, 0.1f));
	}
	selectionValider_ = new Square(-0.1f, -0.6f, 0.25f, 0.1f, 0.1f, 0.1f);
	choixTaille_ = 0;
	choixJ1_ = 0;
	choixJ2_ = 0;
	gameReady_ = false;
}

Menu::~Menu(){}

void Menu::draw(){
	for (int i = 0; i < selectionTaille_.size(); i++){
		GraphicPrimitives::drawFillRect2D(-0.475f + (i / 4.0f), 0.3f, 0.2f, 0.2f, selectionTaille_[i]->getRed(), selectionTaille_[i]->getGreen(), selectionTaille_[i]->getBlue());
		switch (i)
		{
		case 0:
			GraphicPrimitives::drawText2D("3", -0.39 + (i / 4.0f), 0.38f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			GraphicPrimitives::drawText2D("4", -0.39 + (i / 4.0f), 0.38f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			GraphicPrimitives::drawText2D("5", -0.39 + (i / 4.0f), 0.38f, 1.0f, 1.0f, 1.0f);
			break;
		case 3:
			GraphicPrimitives::drawText2D("10", -0.41 + (i / 4.0f), 0.38f, 1.0f, 1.0f, 1.0f);
			break;
		}
	}
	GraphicPrimitives::drawText2D("Joueur 1 :", -0.1f, 0.25f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < selectionJ1_.size(); i++){
		GraphicPrimitives::drawFillRect2D(-0.9f + (i / 2.0f), 0.0f, 0.4f, 0.25f, selectionJ1_[i]->getRed(), selectionJ1_[i]->getGreen(), selectionJ1_[i]->getBlue());
		switch (i)
		{
		case 0:
			GraphicPrimitives::drawText2D("Random", -0.8 + (i / 2.0f), 0.11f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			GraphicPrimitives::drawText2D("Min-Max", -0.825 + (i / 2.0f), 0.11f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			GraphicPrimitives::drawText2D("Alpha-Beta", -0.85 + (i / 2.0f), 0.11f, 1.0f, 1.0f, 1.0f);
			break;
		case 3:
			GraphicPrimitives::drawText2D("Humain", -0.8 + (i / 2.0f), 0.11f, 1.0f, 1.0f, 1.0f);
			break;
		}
	}
	for (int i = 0; i < selectionJ2_.size(); i++){
		GraphicPrimitives::drawFillRect2D(-0.9f + (i / 2.0f), -0.3f, 0.4f, 0.25f, selectionJ2_[i]->getRed(), selectionJ2_[i]->getGreen(), selectionJ2_[i]->getBlue());
		switch (i)
		{
		case 0:
			GraphicPrimitives::drawText2D("Random", -0.8 + (i / 2.0f), -0.19f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			GraphicPrimitives::drawText2D("Min-Max", -0.825 + (i / 2.0f), -0.19f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			GraphicPrimitives::drawText2D("Alpha-Beta", -0.85 + (i / 2.0f), -0.19f, 1.0f, 1.0f, 1.0f);
			break;
		case 3:
			GraphicPrimitives::drawText2D("Humain", -0.8 + (i / 2.0f), -0.19f, 1.0f, 1.0f, 1.0f);
			break;
		}
	}
	GraphicPrimitives::drawFillRect2D(-0.2f, -0.6f, 0.4f, 0.25f, 0.1f, 0.1f, 0.1f);
	GraphicPrimitives::drawText2D("Valider", -0.1f, -0.5f, 1.0f, 1.0f, 1.0f);
}

void Menu::setColor(float f){
	red_ = f;
	green_ = f;
	blue_ = f;
}

void Menu::clickTaille(Morpion *morpion, float posx, float posy){
	for (int k = 0; k < selectionTaille_.size(); k++){
		if ((posx >= selectionTaille_[k]->getX()) && (posx <= selectionTaille_[k]->getX() + 0.3f) && (posy >= selectionTaille_[k]->getY()) && (posy <= selectionTaille_[k]->getY() + 0.2f)){
			for (int l = 0; l < selectionTaille_.size(); l++)
			{
				selectionTaille_[l]->setCptClick(0);
				selectionTaille_[l]->setColor(0.1f, 0.1f, 0.1f);
			}
			selectionTaille_[k]->setCptClick(1);
			selectionTaille_[k]->setColor(0.5f, 0.5f, 0.5f);
			incChoixTaille();
			switch (k)
			{
			case 0:
				(*morpion).setSize(Constants::TAILLE_MORPION_3);
				break;
			case 1:
				(*morpion).setSize(Constants::TAILLE_MORPION_4);
				break;
			case 2:
				(*morpion).setSize(Constants::TAILLE_MORPION_5);
				break;
			case 3:
				(*morpion).setSize(Constants::TAILLE_MORPION_10);
				break;
			}
		}
	}
}

void Menu::clickJ1(float posx, float posy){
	for (int k = 0; k < selectionJ1_.size(); k++){
		if ((posx >= selectionJ1_[k]->getX()) && (posx <= selectionJ1_[k]->getX() + 0.3f) && (posy >= selectionJ1_[k]->getY()) && (posy <= selectionJ1_[k]->getY() + 0.2f)){
			for (int l = 0; l < selectionJ1_.size(); l++)
			{
				selectionJ1_[l]->setCptClick(0);
				selectionJ1_[l]->setColor(0.1f, 0.1f, 0.1f);
			}
			selectionJ1_[k]->setCptClick(1);
			selectionJ1_[k]->setColor(0.5f, 0.5f, 0.5f);
			incChoixJ1();
			switch (k)
			{
			case 0:

				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
	}
}

void Menu::clickJ2(float posx, float posy){
	for (int k = 0; k < selectionJ2_.size(); k++){
		if ((posx >= selectionJ2_[k]->getX()) && (posx <= selectionJ2_[k]->getX() + 0.3f) && (posy >= selectionJ2_[k]->getY()) && (posy <= selectionJ2_[k]->getY() + 0.2f)){
			for (int l = 0; l < selectionJ2_.size(); l++)
			{
				selectionJ2_[l]->setCptClick(0);
				selectionJ2_[l]->setColor(0.1f, 0.1f, 0.1f);
			}
			selectionJ2_[k]->setCptClick(1);
			selectionJ2_[k]->setColor(0.5f, 0.5f, 0.5f);
			incChoixJ2();
			switch (k)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
	}
}

void Menu::clickValider(Morpion *morpion, float posx, float posy){
	if ((posx >= selectionValider_->getX()) && (posx <= selectionValider_->getX() + 0.3f) && (posy >= selectionValider_->getY()) && (posy <= selectionValider_->getY() + 0.2f) && choixOK()){
		(*morpion).init();
		setReady();
	}
}