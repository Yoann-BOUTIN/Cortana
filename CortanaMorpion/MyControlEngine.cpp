#include "MyControlEngine.h"


void MyControlEngine::MouseCallback(int button, int state, int x, int y){
	float posX = ((x - (Constants::WINDOW_WIDTH / 2.0f)) / (float)(Constants::WINDOW_WIDTH / 2.0f))+1;
	float posY = ((y - (Constants::WINDOW_HEIGHT / 2.0f)) / -(float)(Constants::WINDOW_HEIGHT / 2.0f))+1;
	
	if ((*menu_).isSelectionDone())
	{
		//LE JOUEUR CLIQUE BOUTON GAUCHE ET PARTIE NON GAGNEE
		if ((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) && !(*morpion_).getEndGame())
		{
			int i = (int)(posY / (*morpion_).getSquareSize());
			int j = (int)(posX / (*morpion_).getSquareSize());

			// VERIFICATION QUE LA CASE EST VIDE
			if ((*morpion_).getSquare(i, j)->getCptClick() == 0){
				//VERIFIE QUE C EST BIEN AU JOUEUR DE JOUER
				if ((*morpion_).getCurrentPlayer() == Constants::PLAYER)
				{
					//CASE COCHEE ET CHANGEMENT DU JOUEUR COURANT
					(*morpion_).play(i, j, (*player_)[0]->getShape());
				}
			}
		}
	}
	else
	{
		float posx = ((x - (Constants::WINDOW_WIDTH / 2.0f)) / (float)(Constants::WINDOW_WIDTH / 2.0f));
		float posy = ((y - (Constants::WINDOW_HEIGHT / 2.0f)) / -(float)(Constants::WINDOW_HEIGHT / 2.0f));
		(*menu_).clickTaille(morpion_, posx, posy);
		(*menu_).clickJ1(posx, posy);
		(*menu_).clickJ2(posx, posy);
		(*menu_).clickValider(morpion_, posx, posy);
	}
}