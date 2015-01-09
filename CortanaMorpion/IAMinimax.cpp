#include "IAMinimax.h"


IAMinimax::IAMinimax(const int shape, Morpion * morpion) : ordi_(Constants::EMPTY)
{
	srand(time(NULL));
	shape_ = shape;
	morpion_ = morpion;
	prof_ = 2;
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
					int tmp = calcMin(prof_);
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
		//Si l'IA a gagné, on retourne 1000 - le nombre de pions
		if ((*morpion_).getCroixWin())
			return 1000 - comptePions();
		//Egalite -> on retourne 0	
		else if ((*morpion_).isFull())
			return 0;
		//Si l'IA a perdu, on retourne -1000 + le nombre de pions
		else
			return -1000 + comptePions();
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
					if ((*morpion_).getSquare(i + k, i + j)->getForme() == (*morpion_).getCurrentShape()){
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
					if ((*morpion_).getSquare(i + k, ((*morpion_).getSize() - 1) - (i + j))->getForme() == (*morpion_).getCurrentShape()){
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
					if ((*morpion_).getSquare(i, j)->getForme() == (*morpion_).getCurrentShape()){
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
					if ((*morpion_).getSquare(j, i)->getForme() == (*morpion_).getCurrentShape()){
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
	/*int resj1;
	int resj2;
	resj1 = verifLigne(morpion_, Constants::CROIX, nbVerif, nbDecalage) + verifColonne(morpion_, Constants::CROIX, nbVerif, nbDecalage)
		+ verifDiagD(morpion_, Constants::CROIX, nbVerif, nbDecalage) + verifDiagG(morpion_, Constants::CROIX, nbVerif, nbDecalage);

	resj2 = verifLigne(morpion_, Constants::ROND, nbVerif, nbDecalage) + verifColonne(morpion_, Constants::ROND, nbVerif, nbDecalage)
		+ verifDiagD(morpion_, Constants::ROND, nbVerif, nbDecalage) + verifDiagG(morpion_, Constants::ROND, nbVerif, nbDecalage);

	if (shape_ == Constants::CROIX){
		score += (resj1 - resj2);
	}
	else if (shape_ == Constants::ROND){
		score += (resj2 - resj1);
	}*/

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
		return 50 * cntjoueur;
	case 4:
		return 70 * cntjoueur;
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

int IAMinimax::verifLigne(Morpion *morpion, int shape, int nbVerif, int nbDecallage){
	int res = 0;
	int compteur;
	for (int i = 0; i < (*morpion).getSize(); i++){
		for (int j = 0; j < nbDecallage; j++){
			compteur = 0;
			for (int k = j; k < nbVerif + k; j++){
				if ((*morpion).getSquare(i, k)->getForme() == shape){
					compteur++;
				}
				if (compteur == (nbVerif - 1)){
					res++;
				}
			}
		}
	}
	return res;
}

int IAMinimax::verifColonne(Morpion *morpion, int shape, int nbVerif, int nbDecallage){
	int res = 0;
	int compteur;
	for (int i = 0; i < (*morpion).getSize(); i++){
		for (int j = 0; j < nbDecallage; j++){
			compteur = 0;
			for (int k = j; k < nbVerif + j; k++){
				if (!(*morpion).isSquareEmpty(k, i))
				{
					if ((*morpion).getSquare(k, i)->getForme() == shape){
						compteur++;
					}
					if (compteur == (nbVerif - 1)){
						res++;
					}
				}
			}
		}
	}
	return res;
}

int IAMinimax::verifDiagG(Morpion *morpion, int shape, int nbVerif, int nbDecallage){
	int res = 0;
	int compteur;
	for (int i = 0; i < nbDecallage; i++){
		for (int j = 0; j < nbDecallage; j++){
			compteur = 0;
			for (int k = 0; k < nbVerif; k++){
				if ((*morpion).getSquare(i + k, ((*morpion).getSize() - 1) - (j + k))->getForme() == shape){
					compteur++;
				}
				if (compteur == (nbVerif - 1)){
					res++;
				}
			}
		}
	}
	return res;
}

int IAMinimax::verifDiagD(Morpion *morpion, int shape, int nbVerif, int nbDecallage){
	int res = 0;
	int compteur;
	for (int i = 0; i < nbDecallage; i++){
		for (int j = 0; j < nbDecallage; j++){
			compteur = 0;
			for (int k = 0; k < nbVerif; k++){
				if ((*morpion).getSquare(i + k, j + k)->getForme() == shape){
					compteur++;
				}
				if (compteur == (nbVerif - 1)){
					res++;
				}
			}
		}
	}
	return res;
}