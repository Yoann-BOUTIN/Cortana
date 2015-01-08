#include "Morpion.h"

Morpion::Morpion(const int size) : size_(size), squareSize_(2.0f / size), nbPions_(0), croixWin_(false), rondWin_(false)
{
	switch (size)
	{
	case 3:case 4:
		nbPionsToWin_ = 3;
		break;
	case 5:
		nbPionsToWin_ = 4;
		break;
	case 10:
		nbPionsToWin_ = 5;
		break;
	default:
		nbPionsToWin_ = 0;
		break;
	}
}

Morpion::~Morpion(){}

//CREATION DES CARRES 
void Morpion::init()
{
	for (int ligne = 0; ligne < size_; ligne++)
	{
		squares_.emplace_back();
		for (int colonne = 0; colonne < size_; colonne++)
		{
			squares_[ligne].emplace_back(new Square(
				-1 + (colonne* squareSize_),
				-1 + (ligne * squareSize_),
				squareSize_,
				0.0f,
				0.0f,
				0.0f));
		}
	}
}
/**
* VERIFICATION VICTOIRE LIGNE
* Fonction qui compte le nombre d'occurence d'une forme
* sur une même ligne
*/
bool Morpion::verifLigne(int ligne, int colonne, int forme){
	int compteur = 1;
	switch (size_)
	{
		//MORPION TAILLE 3
	case 3:
		if (colonne == 0){
			for (int i = 1; i < 3; i++){
				if (getSquare(ligne, i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
		//MORPION TAILLE 4
	case 4:
		if (colonne <= 1){
			for (int i = 1; i < 3; i++){
				if (getSquare(ligne, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
		//MORPION TAILLE 5
	case 5:
		if (colonne <= 1){
			for (int i = 1; i < 4; i++){
				if (getSquare(ligne, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
		//MORPION TAILLE 10
	case 10:
		if (colonne <= 5){
			for (int i = 1; i < 5; i++){
				if (getSquare(ligne, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	}
}
/**
* VERIFICATION VICTOIRE COLONNE
* Fonction qui compte le nombre d'occurence d'une forme
* sur une même colonne
*/
bool Morpion::verifColonne(int ligne, int colonne, int forme){
	int compteur = 1;
	switch (size_)
	{
	case 3:
		if (ligne == 0){
			for (int i = 1; i < 3; i++){
				if (getSquare(i, colonne)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 4:
		if (ligne <= 1){
			for (int i = 1; i < 3; i++){
				if (getSquare(ligne + i, colonne)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 5:
		if (ligne <= 1){
			for (int i = 1; i < 4; i++){
				if (getSquare(ligne + i, colonne)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 10:
		if (ligne <= 5){
			for (int i = 1; i < 5; i++){
				if (getSquare(ligne + i, colonne)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	}
}
/**
* VERIFICATION VICTOIRE DIAGONALE GAUCHE
* Fonction qui compte le nombre d'occurence d'une forme
* sur une même diagonale gauche
*/
bool Morpion::verifDiagoGauche(int ligne, int colonne, int forme){
	int compteur = 1;
	switch (size_)
	{
	case 3:
		if ((ligne == 0) && (colonne == size_ - 1)){
			for (int i = 1; i < 3; i++){
				if (getSquare(i, colonne - i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 4:
		if ((ligne <= 1) && (colonne >= size_ - 2)){
			for (int i = 1; i < 3; i++){
				if (getSquare(ligne + i, colonne - i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 5:
		if ((ligne <= 1) && (colonne >= size_ - 2)){
			for (int i = 1; i < 4; i++){
				if (getSquare(ligne + i, colonne - i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 10:
		if ((ligne <= 5) && (colonne >= size_ - 6)){
			for (int i = 1; i < 5; i++){
				if (getSquare(ligne + i, colonne - i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	}
}
/**
* VERIFICATION VICTOIRE DIAGONALE DROITE
* Fonction qui compte le nombre d'occurence d'une forme
* sur une même diagonale droite
*/
bool Morpion::verifDiagoDroite(int ligne, int colonne, int forme){
	int compteur = 1;
	switch (size_)
	{
	case 3:
		if ((ligne == 0) && (colonne == 0)){
			for (int i = 1; i < 3; i++){
				if (getSquare(i, i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 4:
		if ((ligne <= 1) && (colonne <= 1)){
			for (int i = 1; i < 3; i++){
				if (getSquare(ligne + i, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 5:
		if ((ligne <= 1) && (colonne <= 1)){
			for (int i = 1; i < 4; i++){
				if (getSquare(ligne + i, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	case 10:
		if ((ligne <= 5) && (colonne <= 5)){
			for (int i = 1; i < 5; i++){
				if (getSquare(ligne + i, colonne + i)->getForme() == forme){
					compteur += 1;
					if (compteur == nbPionsToWin_){
						return true;
					}
				}
				else{
					return false;
				}
			}
		}
		else{
			return false;
		}
		break;
	}
}
/**
* VERIFICATION VICTOIRE
* Fonction qui détermine s'il y a un vainqueur
*/
void Morpion::endGame(){
	for (int i = 0; i < size_; i++){
		for (int j = 0; j < size_; j++){
			if (getSquare(i, j)->getCptClick() == 1){
				switch (getSquare(i, j)->getForme())
				{
				case Constants::CROIX:
					if (verifColonne(i, j, Constants::CROIX) || verifDiagoDroite(i, j, Constants::CROIX) || verifDiagoGauche(i, j, Constants::CROIX) || verifLigne(i, j, Constants::CROIX)){
						winner_ = currentPlayer_;
						croixWin_ = true;
						endGame_ = true;
					}
					break;
				case Constants::ROND:
					if (verifColonne(i, j, Constants::ROND) || verifDiagoDroite(i, j, Constants::ROND) || verifDiagoGauche(i, j, Constants::ROND) || verifLigne(i, j, Constants::ROND)){
						winner_ = currentPlayer_;
						rondWin_ = true;
						endGame_ = true;
					}
					break;
				}
			}
		}
	}
}

void Morpion::play(int i, int j, int shape)
{
	getSquare(i, j)->setForme(shape);
	getSquare(i, j)->incCptClick();
	incNbPions();
	changeCurrentPlayer();
	//std::cout << "PLAY" << std::endl;
}

void Morpion::annuleCoup(int i, int j)
{
	getSquare(i, j)->restoreCptClick();
	getSquare(i, j)->setForme(Constants::EMPTY);
	decNbPions();
	changeCurrentPlayer();
	//std::cout << "ANNULE" << std::endl;
}

void Morpion::changeCurrentPlayer()
{
	switch ((*players_).size())
	{
	case 0:
		currentPlayer_ = (currentPlayer_ == Constants::ORDI_TWO) ? Constants::ORDI : Constants::ORDI_TWO;
		currentShape_ = (currentShape_ == Constants::CROIX) ? Constants::ROND : Constants::CROIX;
		break;
	case 1:
		if (currentPlayer_ == Constants::PLAYER)
		{

		}
		else if (currentPlayer_ == Constants::PLAYER_TWO)
		{

		}
		else
		{

		}
		break;
	case 2:
		currentPlayer_ = (currentPlayer_ == Constants::PLAYER) ? Constants::PLAYER_TWO : Constants::PLAYER;
		currentShape_ = (currentShape_ == Constants::CROIX) ? Constants::ROND : Constants::CROIX;
		break;
	}
	currentPlayer_ = (currentPlayer_ == Constants::PLAYER) ? Constants::ORDI : Constants::PLAYER;
}