#include "Reine.h"



std::shared_ptr<Piece> Reine::getInstanceReine(Couleur couleur) {

	if (reine1 == nullptr && couleur == Couleur::blanc) {

		reine1 = make_shared<Reine>(Reine({ 0,4 }, Couleur::blanc, "Reine blanc"));
		return reine1;
	}

	else if (reine1 != nullptr && couleur == Couleur::blanc) {

		return reine1;
	}

	if (reine2 == nullptr && couleur == Couleur::noir) {

		reine2 = make_shared<Reine>(Reine({ 7,4 }, Couleur::noir, "Reine noir"));
		return reine2;
	}

	else if (reine2 != nullptr && couleur == Couleur::noir) {

		return reine2;
	}
}





Reine::Reine(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {

	cout << "La piece " << this->nom_ << " a ete cree a l'endroit ";
	position.positionNumerotation();
	cout << "\n";

}

bool Reine::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	if (Fou::validationMouvement(positionApres, tableauEchec) or Tour::validationMouvement(positionApres, tableauEchec)) {
		return true;
	}
	return false;

}

bool Reine::verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	if (Fou::verificationAutrePiece(position, tableauEchec) or Tour::verificationAutrePiece(position, tableauEchec)) {
		return true;
	}
	return false;
}
