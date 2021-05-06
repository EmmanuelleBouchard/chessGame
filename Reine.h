#pragma once
#include "Tour.h"
#include "Fou.h"
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"

class Reine : public Fou, public Tour{

public:

	static shared_ptr<Piece> getInstanceReine(Couleur couleur);




private:


	 bool verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec);
	 bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);


	Reine(Position position, Couleur couleur, string nom);

	friend class PlateauEchec;

	inline static shared_ptr<Piece> reine1 = nullptr;
	inline static shared_ptr<Piece> reine2 = nullptr;


};

