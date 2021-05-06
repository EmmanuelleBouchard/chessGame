#pragma once
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"

using namespace std;



class Tour : virtual public Piece{
public:

	static shared_ptr<Piece> getInstanceTourGauche(Couleur couleur);
	static shared_ptr<Piece> getInstanceTourDroite(Couleur couleur);
	
protected:
	Tour() = default;
	virtual bool verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec);
	virtual bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);

private:


	


	Tour(Position position, Couleur couleur, string nom);

	friend class PlateauEchec;

	inline static shared_ptr<Piece> tour1 = nullptr;
	inline static shared_ptr<Piece> tour2 = nullptr;

	inline static shared_ptr<Piece> tour3 = nullptr;
	inline static shared_ptr<Piece> tour4 = nullptr;


};

