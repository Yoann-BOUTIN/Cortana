#pragma once
#include "Square.h"
#include "Constants.h"
#include "Player.h"

class Morpion
{
private:
	std::vector<std::vector<Square *> > squares_; // vecteur de vecteur de case
	std::vector<Player *> players_; // vecteur de joueur
	
	float squareSize_;
	
	int size_;
	int nbPionsToWin_;
	int nbPions_;
	int currentPlayer_;
	int currentShape_;
	int winner_;
	
	bool endGame_;
	bool croixWin_;
	bool rondWin_;

public:
	Morpion(const int size);
	~Morpion();

	Square* getSquare(int i, int j){ return squares_[i][j]; } // renvoi la case dans le vecteur de vecteur de case ayant pour coordonnee i,j
	
	float getSquareSize(){ return squareSize_; }
	
	int getSize(){ return size_; } // renvoi la taille de la grille (3 pour 3x3, 5 pour 5x5, 10 pour 10x10)
	int getCurrentPlayer() { return currentPlayer_; } // renvoi le joueur actuel au moment ou la fonction est appelee
	int getCurrentShape(){ return currentShape_; } // renvoi la forme actuelle au moment ou la fonction est appelee

	void init(); // initialise la grille de morpion 
	void play(int i, int j, int shape); // place un pion sur la case de coordonnee i, j avec la forme shape
	void annuleCoup(int i, int j); // annule le dernier pion placé
	void setCurrentPlayer(int current, int shape){ currentPlayer_ = current; currentShape_ = shape; } // modifie le joueur courant
	void changeCurrentPlayer(); // designe le joueur qui n'était pas le joueur courant comme etant le joueur courant (changement de joueur courant)
	void incNbPions(){ nbPions_++; } // increment le nombre de pions
	void decNbPions(){ nbPions_--; } // decrement le nombre de pions
	void endGame(); // verifie toutes les cases du tableau en faisant des series de longueur variable selon la taille du morpion afin de savoir si la partie est terminee ou non
	void setEndGame(bool end){ endGame_ = end; } // modifie le statut de fin de partie
	void setPlayers(std::vector<Player * >players){ players_ = players; } // modifie le vecteur de joueur
	
	bool isSquareEmpty(int i, int j){ return squares_[i][j]->getCptClick() == 0; } // verifie si la case de coordonnee i, j est vide (true si oui, sinon false)
	bool isFull(){  return nbPions_ >= size_ * size_; } // verifie si le plateau est plein
	bool getEndGame(){ return isFull() || isWin(); } // renvoi true si la partie est termine sinon false
	bool getRondWin(){ return rondWin_; } // renvoi le statut de victoire des carres (true si ils ont gagne sinon false)
	bool getCroixWin(){ return croixWin_; } // renvoi le statut de victoire des croix (truc si ils gagne sinon false)
	bool verifLigne(int ligne, int colonne, int forme); // fonction qui parcours toutes les possibilites sur toutes les lignes par serie de longueur variable selon la taille du morpion 
	bool verifColonne(int ligne, int colonne, int forme); // fonction qui parcours toutes les possibilites sur toutes les colonnes par serie de longueur variable selon la taille du morpion
	bool verifDiagoGauche(int ligne, int colonne, int forme); // fonction qui parcours toutes les possibilites sur toutes les diagonales gauche par serie de longueur variable selon la taille du morpion
	bool verifDiagoDroite(int ligne, int colonne, int forme); // fonction qui parcours toutes les possibilites sur toutes les diagonales droite par serie de longueur variable selon la taille du morpion
	bool isWin(){ return croixWin_ || rondWin_; } //fonction qui verifie si un des deux joueurs a ete declare vainqueur

};

