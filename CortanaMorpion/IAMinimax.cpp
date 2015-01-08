#include "IAMinimax.h"


IAMinimax::IAMinimax(const int shape, Morpion * morpion) : ordi_(Constants::EMPTY)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	prof_ = 3;
	cptEval_ = 0;
}


IAMinimax::~IAMinimax(){}

void IAMinimax::calculIA()
{
	// JOUEUR COURANT EST L ORDI
	cptEval_ = 0;
	int maxi = -1;
	int maxj = -1;
	int max = MINEVAL;
	//Si la profondeur est nulle ou la partie est finie,
	ordi_ = (*morpion_).getCurrentPlayer();
	//on ne fait pas le calcul
	if (prof_ != 0 || !(*morpion_).getEndGame())
	{
		//On parcourt les cases du morpion
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				//Si la case est vide
				if ((*morpion_).isSquareEmpty(i, j))
				{
				//On simule qu'on joue cette case
					(*morpion_).play(i, j, (*morpion_).getCurrentShape());
				//On appelle la fonction calcMin pour lancer l'IA
					int tmp = calcMin((prof_ - 1));
				//Si ce score est plus grand
					if (tmp > max || (tmp == max && rand() % 2 == 0))
					{
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
	(*morpion_).play(maxi, maxj, (*morpion_).getCurrentShape());
}


int IAMinimax::calcMin(int prof)
{
	//LA ON MINIMISE LE COUP DU JOUEUR
	int min = MAXEVAL;
	
	//Si on est à la profondeur voulue, on retourne l'évaluation
	if (prof == 0) return evalue();
	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((*morpion_).getEndGame()) return evalue();
	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if ((*morpion_).isSquareEmpty(i,j)){
			//On joue le coup
				(*morpion_).play(i, j, (*morpion_).getCurrentShape());
			//Maintenant tour de l'ordi donc on cherche a max!
				int tmp = calcMax(prof - 1);
				if (tmp < min){
					tmp = min;
				}
			//On annule le coup
				(*morpion_).annuleCoup(i, j);
			}
		}
	}
	return min;
}

int IAMinimax::calcMax(int prof)
{
	int max = MINEVAL;
	//Si on est à la profondeur voulue, on retourne l'évaluation
	if (prof == 0) return evalue();
	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((*morpion_).getEndGame()) return evalue();
	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (int i= 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if ((*morpion_).isSquareEmpty(i, j)){
			//On joue le coup
				(*morpion_).play(i, j, (*morpion_).getCurrentPlayer());
				int tmp = calcMin(prof - 1);
				if (tmp > max){
					max = tmp;
				}
			//On annule le coup
				(*morpion_).annuleCoup(i, j);
			}
		}
	}
	return max;
}

int IAMinimax::evalue()
{
	// Incrementer le compteur d'evaluation
	cptEval_++;
	int score = 0;
	//Si le jeu est fini
	if ((*morpion_).getEndGame()){
		//Si l'IA a gagné, on retourne 1000 - le nombre de pions
		if ((*morpion_).getCroixWin())
			return 1000;
		//Egalite -> on retourne 0	
		else if (!(*morpion_).isWin())
			return 0;
		//Si l'IA a perdu, on retourne -1000 + le nombre de pions
		else
			return -1000;
	}
	int cntpion = 0;
	int cntjoueur = 0;
	//On regarde chaque case
	for (int i = 0; i<3; i++)
	{
		//Si la case n'est pas vide
		if (!(*morpion_).isSquareEmpty(i, i))
		{
			//On incrémente d'un pion
			cntpion++;
			//Si c'est le même type du joueur courant
			if ((*morpion_).getSquare(i, i)->getForme() == ordi_)
				//On incrémente le compteur
				cntjoueur++;
			else
				//On décrémente le compteur
				cntjoueur--;
		}
	}

	score += calcScore(cntpion, cntjoueur);

	//Diagonale 2
	cntpion = 0;
	cntjoueur = 0;
	for (int i = 0; i<3; i++)
	{
		if (!(*morpion_).isSquareEmpty(i, 2 - i))
		{
			cntpion++;
			if ((*morpion_).getSquare(i, 2 - i)->getForme() == ordi_)
				cntjoueur++;
			else
				cntjoueur--;
		}
	}

	score += calcScore(cntpion, cntjoueur);

	//Lignes
	for (int i = 0; i<3; i++)
	{
		cntpion = 0;
		cntjoueur = 0;
		for (int j = 0; j<3; j++)
		{
			if (!(*morpion_).isSquareEmpty(i, j) )
			{
				cntpion++;
				if ((*morpion_).getSquare(i, j)->getForme() == ordi_)
					cntjoueur++;
				else
					cntjoueur--;
			}
		}

		score += calcScore(cntpion, cntjoueur);
	}

	//Colonnes
	for (int i = 0; i<3; i++)
	{
		cntpion = 0;
		cntjoueur = 0;
		for (int j = 0; j<3; j++)
		{
			if (!(*morpion_).isSquareEmpty(j,i))
			{
				cntpion++;
				if ((*morpion_).getSquare(j, i)->getForme() == ordi_)
					cntjoueur++;
				else
					cntjoueur--;
			}
		}

		score += calcScore(cntpion, cntjoueur);
	}

	return score;
}


int IAMinimax::calcScore(int cntpion, int cntjoueur)
{
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