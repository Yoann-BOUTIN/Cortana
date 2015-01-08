#include "IAMinimax.h"


IAMinimax::IAMinimax(const int shape, Morpion * morpion)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	prof_ = 9;
	cptEval_ = 0;
}


IAMinimax::~IAMinimax(){}

void IAMinimax::calculIA(Morpion * morpion, int prof)
{
	// JOUEUR COURANT EST L ORDI
	int i, j, tmp;
	int max = MINEVAL;
	int maxi = -1, maxj = -1;


	//Si la profondeur est nulle ou la partie est finie,
	//on ne fait pas le calcul
	if ((prof != 0) || (!(*morpion).getEndGame()))
	{
		//On parcourt les cases du morpion
		for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			//Si la case est vide
			if ((*morpion).isSquareEmpty(i, j))
			{
				//On simule qu'on joue cette case
				(*morpion).play(i, j, (*morpion).getCurrentShape());
				//On appelle la fonction calcMin pour lancer l'IA
				tmp = calcMin(morpion, prof - 1);
				//Si ce score est plus grand
				if ((tmp>max) || ((tmp == max) && (rand() % 2 == 0)))
				{
					//On le choisit
					max = tmp;
					maxi = i;
					maxj = j;
				}
				//On annule le coup
				(*morpion).annuleCoup(i, j);
			}
		}
	}
	//On jouera le coup maximal
	(*morpion).play(maxi, maxj, getShape());
}


int IAMinimax::calcMin(Morpion *morpion, int prof)
{
	//LA ON MINIMISE LE COUP DU JOUEUR
	int i, j, tmp;
	int min = MAXEVAL;
	
	//Si on est à la profondeur voulue, on retourne l'évaluation
	if (prof == 0)
		return evalue(morpion);

	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((*morpion).getEndGame())
		return evalue(morpion);

	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	{
		if ((*morpion).isSquareEmpty(i, j))
		{
			//On joue le coup
			(*morpion).play(i, j,(*morpion).getCurrentShape());
			//Maintenant tour de l'ordi donc on cherche a max!
			tmp = calcMax(morpion, prof - 1);
			if (tmp<min)
			{
				min = tmp;
			}
		//On annule le coup
		(*morpion).annuleCoup(i, j);
		}
	}
	return min;
}

int IAMinimax::calcMax(Morpion *morpion, int prof)
{
	int i, j, tmp;
	int max = MINEVAL;

	//Si on est à la profondeur voulue, on retourne l'évaluation
	if (prof == 0)
	{
		return evalue(morpion);
	}

	//Si la partie est finie, on retourne l'évaluation de jeu
	if ((*morpion).getEndGame())
		return evalue(morpion);

	//On parcourt le plateau de jeu et on le joue si la case est vide
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	{
		if ((*morpion).isSquareEmpty(i, j))
		{
			//On joue le coup
			(*morpion).play(i, j, (*morpion).getCurrentShape());
			tmp = calcMin(morpion, prof - 1);
			if (tmp > max)
			{
				max = tmp;
			}
			//On annule le coup
			(*morpion).annuleCoup(i, j);
		}
	}
	return max;
}

int IAMinimax::evalue(Morpion * morpion)
{
	int score = 0;

	int cntjoueur, cntIa;
	int i, j;

	// Incrementer le compteur d'evaluation
	cptEval_++;

	//Si le jeu est fini
	if ((*morpion).getEndGame())
	{
		//Si l'IA a gagné, on retourne 1000 - le nombre de pions
		if ((*morpion).getWinner() == Constants::ORDI)
		{
			return 1000;
		}
		else if (!(*morpion).isWin())
		{
			//Egalite -> on retourne 0	
			return 0;
		}
		else
		{
			//Si l'IA a perdu, on retourne -1000 + le nombre de pions
			return -1000;
		}
	}

	//Diagonale 1
	cntIa = 0;
	cntjoueur = 0;
	//On regarde chaque case
	for (i = 0; i<3; i++)
	{
		//Si la case n'est pas vide
		if (!(*morpion).isSquareEmpty(i, i))
		{
			//On incrémente d'un pion
			//Si c'est le même type du joueur courant
			if ((*morpion).getSquare(i, i)->getForme() == (*morpion).getCurrentShape())
			{
				if ((*morpion).getCurrentShape() == Constants::CROIX)
					//On incrémente le compteur
					cntjoueur++;
				else
					//On décrémente le compteur
					cntIa++;
			}
		}
	}
	score += calcScore(cntIa, cntjoueur);

	//Diagonale 2
	cntIa = 0;
	cntjoueur = 0;
	for (i = 0; i<3; i++)
	{
		if (!(*morpion).isSquareEmpty(i, 2 - i))
		{
			if ((*morpion).getSquare(i, 2 - i)->getForme() == (*morpion).getCurrentShape())
			{
				if ((*morpion).getCurrentShape() == Constants::CROIX)
					//On incrémente le compteur
					cntjoueur++;
				else
					//On décrémente le compteur
					cntIa++;
			}
		}
	}

	score += calcScore(cntIa, cntjoueur);

	//Lignes
	for (i = 0; i<3; i++)
	{
		cntIa = 0;
		cntjoueur = 0;
		for (j = 0; j<3; j++)
		{
			if (!(*morpion).isSquareEmpty(i, j))
			{
				if ((*morpion).getSquare(i, j)->getForme() == (*morpion).getCurrentShape())
				{
					if ((*morpion).getCurrentShape() == Constants::CROIX)
						//On incrémente le compteur
						cntjoueur++;
					else
						//On décrémente le compteur
						cntIa++;
				}
			}
		}

		score += calcScore(cntIa, cntjoueur);
	}

	//Colonnes
	for (i = 0; i<3; i++)
	{
		cntIa = 0;
		cntjoueur = 0;
		for (j = 0; j<3; j++)
		{
			if (!(*morpion).isSquareEmpty(j, i))
			{
				if ((*morpion).getSquare(j, i)->getForme() == (*morpion).getCurrentShape())
				{
					if ((*morpion).getCurrentShape() == Constants::CROIX)
						//On incrémente le compteur
						cntjoueur++;
					else
						//On décrémente le compteur
						cntIa++;
				}
			}
		}
		score += calcScore(cntIa, cntjoueur);
	}
	return score;
}


int IAMinimax::calcScore(int cntIa, int cntjoueur)
{
	if (cntIa == cntjoueur) return 0;
	if (cntIa == 2) return 200;
	if (cntIa == 1) return 50;
	if (cntjoueur == 2) return -200;
	if (cntjoueur == 1) return -50;
}

int IAMinimax::comptePions(Morpion * morpion)
{
	int i, j, cnt = 0;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	{
		if (!(*morpion).isSquareEmpty(i, j))
			cnt++;
	}
	return cnt;
}