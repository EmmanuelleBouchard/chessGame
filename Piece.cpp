
#include "Piece.h"
#include <iostream>
#include <string>
#include "Roi.h"
#include "Fou.h"
#include "Cavalier.h"

using namespace std;


Piece::Piece() {

	positionActuelle.x = 0;
	positionActuelle.y = 0;
	couleur_ = Couleur::vide;
	nom_ = "aucun";
}


Piece::Piece(Position position, Couleur couleur, string nom) : positionActuelle(position), couleur_(couleur), nom_(nom) {}


bool Piece::validationMouvement(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	return false;

};

string Piece::getNom() {

	if (this == nullptr) {

		return "Case vide";

	}

	return nom_;
}

Couleur Piece::getCouleur() {
	if (this == nullptr) {
		cout << "La case est vide." << endl;
		return Couleur::vide;
	}

	return couleur_;
};

bool Piece::verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec) {
	if (tableauEchec[position.x][position.y] != nullptr) {
		if ((position.x == this->positionActuelle.x) && (position.y == this->positionActuelle.y))
			cout << "Tentative de deplacement sur la meme case. " << endl;
		return true;
	}


	return false;

}

Position Piece::getPositionActuelle() {
	if (this == nullptr) {

		cout << "La case est vide" << endl;
	}
	else {

		positionActuelle.positionNumerotation();
	}

	return positionActuelle;
}

bool Piece::pareilCouleur(shared_ptr<Piece> piece) {
	if (piece == nullptr) {
		return false;
	}
	if (this->getCouleur() == piece->getCouleur())
		return true;

	return false;
};

