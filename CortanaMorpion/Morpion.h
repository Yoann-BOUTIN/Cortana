#pragma once
#include "Square.h"
#include "Constants.h"
#include "Player.h"

class Morpion
{
private:
	std::vector<std::vector<Square *> > squares_;
	std::vector<Player *> players_;
	
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

	Square* getSquare(int i, int j){ return squares_[i][j]; }
	
	float getSquareSize(){ return squareSize_; }
	
	int getSize(){ return size_; }
	int getCurrentPlayer() { return currentPlayer_; }
	int getCurrentShape(){ return currentShape_; }
	int getWinner(){ return winner_; }

	void init();
	void play(int i, int j, int shape);
	void annuleCoup(int i, int j);
	void setCurrentPlayer(int current, int shape){ currentPlayer_ = current; currentShape_ = shape; }
	void changeCurrentPlayer();
	void incNbPions(){ nbPions_++; }
	void decNbPions(){ nbPions_--; }
	void endGame();
	void setEndGame(bool end){ endGame_ = end; }
	void setPlayers(std::vector<Player * >players){ players_ = players; }
	
	bool isSquareEmpty(int i, int j){ return squares_[i][j]->getCptClick() == 0; }
	bool isFull(){  return nbPions_ >= size_ * size_; }
	bool getEndGame(){ return isFull() || isWin(); }
	bool getRondWin(){ return rondWin_; }
	bool getCroixWin(){ return croixWin_; }
	bool verifLigne(int ligne, int colonne, int forme);
	bool verifColonne(int ligne, int colonne, int forme);
	bool verifDiagoGauche(int ligne, int colonne, int forme);
	bool verifDiagoDroite(int ligne, int colonne, int forme);
	bool isWin(){ return croixWin_ || rondWin_; }

};

