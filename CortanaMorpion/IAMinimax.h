#pragma once
#include "IA.h"

class IAMinimax :
	public IA
{
private:
	int ordi_;
public:
	IAMinimax(const int shape, Morpion * morpion);
	~IAMinimax();

	void calculIA(); // fonction qui va chercher le meilleur coup a jouer pour une IA Min-Max
	int calcMin(int prof); // calcule le coup avec le plus petit score, avec en parametre la profondeur
	int calcMax(int prof); // calcule le coup avec le plus grand score,
	int evalue(); // evaluation de la grille de morpion dans l etat du moment ou la fonction est lance
	int calcScore(int cntpion, int cntjoueur); // fonction appelee lorsque evalue est appele (cas ou la partie n'est pas fini a ce moment la), avec en parametre le nombre de pions et le nombres de l'IA sur une serie (positif si l'IA possede plus de pions sur la serie que l'adversaire, sinon negatif)
	int comptePions(); // compte le nombre de pions sur la grille au moment ou la fonction est appelee
	int getOtherShape(){ return (shape_ == Constants::CROIX) ? Constants::CROIX : Constants::ROND; } // renvoi la forme qui n'est pas la forme courante
};

