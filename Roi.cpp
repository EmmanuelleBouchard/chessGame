#include <iostream>
#include <string>

#include "Roi.h"
#include "Ajout.h"
#include <cmath>
#include "Piece.h"

std::shared_ptr<Piece> Roi::Roi::getInstanceRoi(Couleur couleur) {


	if (roi1 == nullptr && couleur == Couleur::blanc) {

		roi1 = make_shared<Roi>(Roi({ 0,5 }, Couleur::blanc, "Roi blanc"));
		return roi1;
	}

	else if (roi1 != nullptr && couleur == Couleur::blanc) {

		return roi1;
	}

	if (roi2 == nullptr && couleur == Couleur::noir) {

		roi2 = make_shared<Roi>(Roi({ 7,5 }, Couleur::noir, "Roi noir"));
		return roi2;
	}

	else if (roi2 != nullptr && couleur == Couleur::noir) {

		return roi2;
	}
}

void Roi::Roi::effacerInstanceRoi() {

	roi1 = nullptr;
	roi2 = nullptr;

}



bool Roi::Roi::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	//Deplacement horizontale
	if (((abs(positionApres.x - positionActuelle.x) == 1)) && (positionApres.y - positionActuelle.y) == 0) {
		return true;
	}

	//Deplacement verticale
	else if ((positionApres.x - positionActuelle.x == 0) && (abs(positionApres.y - positionActuelle.y)) == 1) {
		return true;
	}

	//Deplacement Diagonale
	else if ((abs(positionApres.x - positionActuelle.x) == 1) && (abs(positionApres.y - positionActuelle.y)) == 1) {
		return true;
	}

	return false;

}

Roi::Roi::Roi(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {

	

}

