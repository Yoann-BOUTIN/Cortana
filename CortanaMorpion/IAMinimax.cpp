#include "IAMinimax.h"


IAMinimax::IAMinimax(const int shape, Morpion * morpion)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	int fact = 1;
	for (int i = 1; i <= (((*morpion).getSize() * (*morpion).getSize())); i++){
		fact = fact * i;
	}
	prof_ = (1);
	cptEval_ = 0;
}


IAMinimax::~IAMinimax(){}

void IAMinimax::calculIA(int prof)
{
	int tmp;
	int max = MINEVAL;
	int maxi = -1, maxj = -1;
	//Si la profondeur est nulle ou la partie est finie,
	//on ne fait pas le calcul
	if ((prof != 0) || (!(*morpion_).getEndGame()))
	{
		//On parcourt les cases du morpion
		for (int i = 0; i < Constants::TAILLE_MORPION; i++){
			for (int j = 0; j<Constants::TAILLE_MORPION; j++)
			{
				//Si la case est vide
				if ((*morpion_).isSquareEmpty(i, j))
				{
					//On simule qu'on joue cette case
					(*morpion_).play(i, j, getShape());
					//On appelle la fonction calcMin pour lancer l'IA
					tmp = calcMin(morpion_, prof);
					//Si ce score est plus grand
					if ((tmp > max))
					{
						std::cout << "Tmp : " << tmp << std::endl;
						//On le choisit
						max = tmp;
						maxi = i;
						maxj = j;
					}
					//On annule le coup
					(*morpion_).annuleCoup(i, j);
				}
			}
		}
	}
	//On jouera le coup maximal
	//std::cout << "COUCOU 2 : " << maxi << std::endl;
	//std::cout << "EVAL : " << cptEval_ << std::endl;

	(*morpion_).play(maxi, maxj, getShape());
}


int IAMinimax::calcMin(Morpion *morpion, int prof)
{
	int tmp;
	int min = MAXEVAL;
	//std::cout << "PROFONDEUR : " << prof << std::endl;

	//Si on est à la profondeur voulue, on retourne l'évaluation
	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((prof == 0) || (*morpion).getEndGame()){
		return evalue(morpion);
	}


	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (int i = 0; i < Constants::TAILLE_MORPION; i++){
		for (int j = 0; j < Constants::TAILLE_MORPION; j++)
		{
			if ((*morpion).isSquareEmpty(i, j))
			{
				//On joue le coup
				(*morpion).play(i, j, getShape());
				tmp = calcMax(morpion, prof - 1);
				if (tmp < min)
				{
					min = tmp;
				}
				//On annule le coup
				(*morpion).annuleCoup(i, j);
			}
		}
		return min;
	}
}

int IAMinimax::calcMax(Morpion *morpion, int prof)
{
	int i, j, tmp;
	int max = MINEVAL;

	//Si on est à la profondeur voulue, on retourne l'évaluation
	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((prof == 0) || (*morpion_).getEndGame()){
		return evalue(morpion);
	}

	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (i = 0; i < Constants::TAILLE_MORPION; i++){
		for (j = 0; j<Constants::TAILLE_MORPION; j++)
		{
			if ((*morpion).isSquareEmpty(i, j))
			{
				//On joue le coup
				(*morpion).play(i, j, getShape());
				tmp = calcMin(morpion, prof - 1);
				if (tmp>max)
				{
					max = tmp;
				}
				//On annule le coup
				(*morpion).annuleCoup(i, j);
			}
		}
		return max;
	}
}

int IAMinimax::evalue(Morpion * morpion)
{
	//std::cout << "EVAL" << std::endl;
	int score = 0;
	int nbVerif;
	int nbDecalage;
	int cntjoueur, cntpion;
	int i, j, k;

	// Incrementer le compteur d'evaluation
	cptEval_ += 1;

	//Si le jeu est fini
	if ((*morpion).getEndGame())
	{
		//Si l'IA a gagné, on retourne 1000 - le nombre de pions
		if ((*morpion).getWinner() == Constants::ORDI)
		{
			return 1000 - comptePions();
		}
		else if (!(*morpion).isWin())
		{
			//Egalite -> on retourne 0	
			return 0;
		}
		else
		{
			//Si l'IA a perdu, on retourne -1000 + le nombre de pions
			return -1000 + comptePions();
		}
	}
	switch ((*morpion).getSize())
	{
	case 3:
		nbVerif = 3;
		nbDecalage = 1;
		break;
	case 4:
		nbVerif = 3;
		nbDecalage = 2;
		break;
	case 5:
		nbVerif = 4;
		nbDecalage = 2;
		break;
	case 10:
		nbVerif = 5;
		nbDecalage = 6;
		break;
	}
	//Diagonale 1

	//On regarde chaque case

	for (k = 0; k < nbDecalage; k++){
		for (j = 0; j < nbDecalage; j++){
			cntpion = 0;
			cntjoueur = 0;
			for (i = 0; i < nbVerif; i++)
			{
				//Si la case n'est pas vide
				if (!(*morpion).isSquareEmpty(i + k, i + j))
				{
					//On incrémente d'un pion
					cntpion++;
					//Si c'est le même type du joueur courant
					int currentShape = ((*morpion).getCurrentPlayer() == Constants::ORDI) ? getShape() : getOtherShape();
					if ((*morpion).getSquare(i + k, i + j)->getForme() == currentShape)
						//On incrémente le compteur
						cntjoueur++;
					else
						//On décrémente le compteur
						cntjoueur--;
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}

	//std::cout << "score " << score << std::endl;
	//Diagonale 2

	for (k = 0; k < nbDecalage; k++){
		for (j = 0; j < nbDecalage; j++){
			cntpion = 0;
			cntjoueur = 0;
			for (i = 0; i < nbVerif; i++)
			{
				if (!(*morpion).isSquareEmpty(i + k, ((*morpion).getSize() - 1) - (i + j)))
				{
					cntpion++;
					int currentShape = ((*morpion).getCurrentPlayer() == Constants::ORDI) ? getShape() : getOtherShape();
					if ((*morpion).getSquare(i + k, ((*morpion).getSize() - 1) - (i + j))->getForme() == currentShape)
						cntjoueur++;
					else
						cntjoueur--;
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}


	//Lignes
	for (i = 0; i<(*morpion).getSize(); i++)
	{
		for (k = 0; k < nbDecalage; k++){
			cntpion = 0;
			cntjoueur = 0;
			for (j = k; j < nbVerif + k; j++)
			{
				if (!(*morpion).isSquareEmpty(i, j))
				{
					cntpion++;
					int currentShape = ((*morpion).getCurrentPlayer() == Constants::ORDI) ? getShape() : getOtherShape();
					if ((*morpion).getSquare(i, j)->getForme() == currentShape)
						cntjoueur++;
					else
						cntjoueur--;
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}

	//Colonnes
	for (i = 0; i<(*morpion).getSize(); i++)
	{
		cntpion = 0;
		cntjoueur = 0;
		for (k = 0; k < nbDecalage; k++){
			for (j = k; j < nbVerif + k; j++)
			{
				if (!(*morpion).isSquareEmpty(j, i))
				{
					cntpion++;
					int currentShape = ((*morpion).getCurrentPlayer() == Constants::ORDI) ? getShape() : getOtherShape();
					if ((*morpion).getSquare(j, i)->getForme() == currentShape)
						cntjoueur++;
					else
						cntjoueur--;
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}
	return score;
}


int IAMinimax::calcScore(int cntpion, int cntjoueur)
{
	//On regarde le nombre de pions
	switch (cntpion)
	{
	case 1:
		return 10 * cntjoueur;
	case 2:
		return 30 * cntjoueur;
	default:
		return 0;
	}
}

int IAMinimax::comptePions()
{
	int i, j, cnt = 0;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	{
		if (!(*morpion_).isSquareEmpty(i, j))
			cnt++;
	}
	return cnt;
}