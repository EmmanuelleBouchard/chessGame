#pragma once
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"

using namespace std;

class Pion : public Piece{

public:

	Pion(Position position, Couleur couleur, string nom);


private:

	bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);

	friend class PlateauEchec;


};

