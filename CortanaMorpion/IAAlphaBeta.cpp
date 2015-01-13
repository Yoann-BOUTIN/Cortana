#include "IAAlphaBeta.h"


IAAlphaBeta::IAAlphaBeta(const int shape, Morpion * morpion) : ordi_(Constants::EMPTY)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	switch ((*morpion).getSize()){
	case 3:
		prof_ = 9;
		break;
	case 5:
		prof_ = 5;
		break;
	case 10:
		prof_ = 2;
		break;
	}
	cptEval_ = 0;
}


IAAlphaBeta::~IAAlphaBeta(){}

void IAAlphaBeta::calculIA()
{
	// JOUEUR COURANT EST L ORDI
	cptEval_ = 0;
	int maxi = -1;
	int maxj = -1;
	int alpha = MINEVAL;
	int beta = MAXEVAL;
	//Si la profondeur est nulle ou la partie est finie,
	ordi_ = (*morpion_).getCurrentShape();

	//on ne fait pas le calcul
	if (comptePions() >= 55 && (*morpion_).getSize() == 10){
		prof_ = 3;
	}
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
					int tmp = calcMin(prof_, alpha, beta);
					//Si ce score est plus grand
					if (alpha < tmp)
					{
						//On le choisit
						alpha = tmp;
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


int IAAlphaBeta::calcMin(int prof, int alpha, int beta)
{

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
				int tmp = calcMax(prof - 1, alpha, beta);

				//On annule le coup
				(*morpion_).annuleCoup(i, j);

				//Mis a jour de beta
				if (beta > tmp)
				{
					beta = tmp;
				}
				if (beta <= alpha)
				{
					return beta;
				}
			}
		}
	}
	return beta;
}

int IAAlphaBeta::calcMax(int prof, int alpha, int beta)
{
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
				int tmp = calcMin(prof - 1, alpha, beta);

				//On annule le coup
				(*morpion_).annuleCoup(i, j);

				if (alpha < tmp)
				{
					alpha = tmp;
				}

				if (beta <= alpha)
				{
					return alpha;
				}
			}
		}
	}
	return alpha;
}

int IAAlphaBeta::evalue()
{
	// Incrementer le compteur d'evaluation
	cptEval_++;
	int nbVerif;
	int nbDecalage;
	int i, j, k;
	int score = 0;
	//Si le jeu est fini
	if ((*morpion_).getEndGame()){
		if ((*morpion_).getSize() == Constants::TAILLE_MORPION_10 && prof_ != 3){
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


int IAAlphaBeta::calcScore(int cntpion, int cntjoueur)
{
	switch (cntpion)
	{
	case 1:
		return 10 * cntjoueur;
	case 2:
		return 30 * cntjoueur;
	case 3:
		if (cntpion == -(cntjoueur) && (*morpion_).getSize() == Constants::TAILLE_MORPION_10 && prof_ != 3){
			return 1000 * cntjoueur;
		}
		return 50 * cntjoueur;
	case 4:
		if ((*morpion_).getSize() == Constants::TAILLE_MORPION_10 && prof_ != 3){
			if (cntpion == cntjoueur){
				return 500 * cntjoueur;
			}
			else if (cntpion == -(cntjoueur))
			{
				return 1000 * cntjoueur;
			}
			else if (cntpion - 2 == -(cntjoueur)){
				return 500 * cntjoueur;
			}
		}
		/*if (cntpion == cntjoueur || cntpion == -(cntjoueur)){
			return 1000 * cntjoueur;
			}*/
		return 70 * cntjoueur;
	case 5:
		if ((*morpion_).getSize() == Constants::TAILLE_MORPION_10 && prof_ != 3){
			if ((cntpion - 4) == -(cntjoueur)){
				return 500 * cntjoueur;
			}
			else if ((cntpion - 2) == cntjoueur){
				return 500 * cntjoueur;
			}
		}
		return 0;
	default:
		return 0;
	}
}

int IAAlphaBeta::comptePions()
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
