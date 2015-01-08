#pragma once
#include "Square.h"
#include "Constants.h"
#include "IA.h"
#include "IAMinimax.h"
#include "IARandom.h"
#include "Player.h"

class Morpion
{
private:
	std::vector<std::vector<Square *> > squares_;
	std::vector< Player *> pl_;
	std::vector< IA *> ia_;
	
	float squareSize_;
	
	int size_;
	int nbPionsToWin_;
	int nbPions_;
	int currentPlayer_;
	int winner_;
	
	bool endGame_;
	bool croixWin_;
	bool rondWin_;

public:
	Morpion(const int);
	~Morpion();

	Square* getSquare(int i, int j){ return squares_[i][j]; }
	void setPlayer(std::vector< Player *> pl){ pl_ = pl; }
	void setIA(std::vector< IA *> ia){ ia_ = ia; }
	IA* getIA(int i){ return ia_[i]; }
	Player* getPlayer(int i){ return pl_[i]; }
	
	float getSquareSize(){ return squareSize_; }
	
	int getSize(){ return size_; }
	int getCurrentPlayer() { return currentPlayer_; }
	int getWinner(){ return winner_; }

	void init();
	void play(int i, int j, int shape);
	void annuleCoup(int i, int j);
	void setCurrentPlayer(int current){ currentPlayer_ = current; }
	void changeCurrentPlayer();
	void incNbPions(){ nbPions_++; }
	void decNbPions(){ nbPions_--; }
	void endGame();
	void setEndGame(bool end){ endGame_ = end; }
	void setSize(int i){ size_ = i; }
	
	bool isSquareEmpty(int i, int j){ return squares_[i][j]->getCptClick() == 0; }
	bool isFull(){ return nbPions_ >= size_ * size_; }
	bool getEndGame(){ return isFull() || isWin(); }
	bool getRondWin(){ return rondWin_; }
	bool getCroixWin(){ return croixWin_; }
	bool verifLigne(int ligne, int colonne, int forme);
	bool verifColonne(int ligne, int colonne, int forme);
	bool verifDiagoGauche(int ligne, int colonne, int forme);
	bool verifDiagoDroite(int ligne, int colonne, int forme);
	bool isWin(){ return croixWin_ || rondWin_; }

};

