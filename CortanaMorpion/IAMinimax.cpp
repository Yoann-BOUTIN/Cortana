#include "IAMinimax.h"


IAMinimax::IAMinimax(const int shape, Morpion * morpion) : ordi_(Constants::EMPTY)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	switch ((*morpion).getSize()){
	case 3:
		prof_ = 9;
		break;
	case 5:
		prof_ = 4;
		break;
	case 10:
		prof_ = 3;
		break;
	}
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
		for (int i = 0; i < (*morpion_).getSize(); i++){
			for (int j = 0; j < (*morpion_).getSize(); j++){
				//Si la case est vide
				if ((*morpion_).isSquareEmpty(i, j))
				{
					//On simule qu'on joue cette case
					(*morpion_).play(i, j, (*morpion_).getCurrentShape());
					//On appelle la fonction calcMin pour lancer l'IA
					int tmp = calcMin(prof_ - 1);
					//Si ce score est plus grand
					if (tmp > max)
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
	for (int i = 0; i < (*morpion_).getSize(); i++){
		for (int j = 0; j < (*morpion_).getSize(); j++){
			if ((*morpion_).isSquareEmpty(i, j)){
				//On joue le coup
				(*morpion_).play(i, j, (*morpion_).getCurrentShape());
				//Maintenant tour de l'ordi donc on cherche a max!
				int tmp = calcMax(prof - 1);
				if (tmp < min){
					min = tmp;
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
	for (int i = 0; i < (*morpion_).getSize(); i++){
		for (int j = 0; j < (*morpion_).getSize(); j++){
			if ((*morpion_).isSquareEmpty(i, j)){
				//On joue le coup
				(*morpion_).play(i, j, (*morpion_).getCurrentShape());
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
	int nbVerif;
	int nbDecalage;
	int i, j, k;
	int score = 0;
	//Si le jeu est fini
	if ((*morpion_).getEndGame()){
		if ((*morpion_).getSize() == Constants::TAILLE_MORPION_10){
			if (((shape_ == Constants::CROIX) && ((*morpion_).getCroixWin())) || ((shape_ == Constants::ROND) && ((*morpion_).getRondWin())))
				return 30000 - comptePions();
			//Egalite -> on retourne 0	
			else if ((*morpion_).isFull())
				return 0;
			//Si l'IA a perdu, on retourne -1000 + le nombre de pions
			else
				return -30000 + comptePions();
		}
		else{
			//Si l'IA a gagné, on retourne 1000 - le nombre de pions
			if (((shape_ == Constants::CROIX) && ((*morpion_).getCroixWin())) || ((shape_ == Constants::ROND) && ((*morpion_).getRondWin())))
				return 1000 - comptePions();
			//Egalite -> on retourne 0	
			else if ((*morpion_).isFull())
				return 0;
			//Si l'IA a perdu, on retourne -1000 + le nombre de pions
			else
				return -1000 + comptePions();
		}
	}

	switch ((*morpion_).getSize())
	{
	case 3:
		nbVerif = 3;
		nbDecalage = 1;
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

	int cntpion = 0;
	int cntjoueur = 0;
	//On regarde chaque case
	for (k = 0; k < nbDecalage; k++){
		for (j = 0; j < nbDecalage; j++){
			cntpion = 0;
			cntjoueur = 0;
			for (i = 0; i < nbVerif; i++)
			{
				//Si la case n'est pas vide
				if (!(*morpion_).isSquareEmpty(i + k, i + j))
				{
					//On incrémente d'un pion
					cntpion++;
					//Si c'est le même type du joueur courant
					if ((*morpion_).getSquare(i + k, i + j)->getForme() == shape_){
						//On incrémente le compteur
						cntjoueur++;
					}
					else{
						//On décrémente le compteur
						cntjoueur--;
					}
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
				if (!(*morpion_).isSquareEmpty(i + k, ((*morpion_).getSize() - 1) - (i + j)))
				{
					cntpion++;
					if ((*morpion_).getSquare(i + k, ((*morpion_).getSize() - 1) - (i + j))->getForme() == shape_){
						cntjoueur++;
					}
					else{
						cntjoueur--;
					}
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}


	//Lignes
	for (i = 0; i < (*morpion_).getSize(); i++)
	{
		for (k = 0; k < nbDecalage; k++){
			cntpion = 0;
			cntjoueur = 0;
			for (j = k; j < nbVerif + k; j++)
			{
				if (!(*morpion_).isSquareEmpty(i, j))
				{
					cntpion++;
					if ((*morpion_).getSquare(i, j)->getForme() == shape_){
						cntjoueur++;
					}
					else{
						cntjoueur--;
					}
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
	}

	//Colonnes
	for (i = 0; i < (*morpion_).getSize(); i++)
	{
		for (k = 0; k < nbDecalage; k++){
			cntpion = 0;
			cntjoueur = 0;
			for (j = k; j < nbVerif + k; j++)
			{
				if (!(*morpion_).isSquareEmpty(j, i))
				{
					cntpion++;
					if ((*morpion_).getSquare(j, i)->getForme() == shape_){
						cntjoueur++;
					}
					else{
						cntjoueur--;
					}
				}
			}
			score += calcScore(cntpion, cntjoueur);
		}
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
	case 3:
		if (cntpion == -(cntjoueur) && (*morpion_).getSize() == Constants::TAILLE_MORPION_10){
			return 400 * cntjoueur;
		}
		return 50 * cntjoueur;
	case 4:
		if ((*morpion_).getSize() == Constants::TAILLE_MORPION_10){
			if (cntpion == -(cntjoueur)){
				return 1000 * cntjoueur;
			}
			else if (cntpion == cntjoueur)
			{
				return 300 * cntjoueur;
			}
			else if (cntpion - 2 == cntjoueur){
				return 200 * cntjoueur;
			}
		}
		return 70 * cntjoueur;
	case 5:
		return 90 * cntjoueur;
	default:
		return 0;
	}
}

int IAMinimax::comptePions()
{
	int i, j, cnt = 0;
	for (i = 0; i < (*morpion_).getSize(); i++)
	for (j = 0; j < (*morpion_).getSize(); j++)
	{
		if (!(*morpion_).isSquareEmpty(i, j))
			cnt++;
	}
	return cnt;
}