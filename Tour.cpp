#include "Tour.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <memory>

#include "Piece.h"
#include "Ajout.h"

std::shared_ptr<Piece> Tour::getInstanceTourGauche(Couleur couleur) {

	if (tour1 == nullptr && couleur == Couleur::blanc) {

		tour1 = make_shared<Tour>(Tour({ 0,8 }, Couleur::blanc, "Tour blanc G"));

		return tour1;
	}
	else if (tour1 != nullptr && couleur == Couleur::blanc) {

		return tour1;
	}

	if (tour2 == nullptr && couleur == Couleur::noir) {

		tour2 = make_shared<Tour>(Tour({ 7,1 }, Couleur::noir, "Tour noir G"));

		return tour2;
	}
	else if (tour2 != nullptr && couleur == Couleur::noir) {

		return tour2;
	}

}


std::shared_ptr<Piece> Tour::getInstanceTourDroite(Couleur couleur) {

	if (tour3 == nullptr && couleur == Couleur::blanc) {

		tour3 = make_shared<Tour>(Tour({ 0,1 }, Couleur::blanc, "Tour blanc D"));

		return tour3;
	}
	else if (tour3 != nullptr && couleur == Couleur::blanc) {

		return tour3;
	}

	if (tour4 == nullptr && couleur == Couleur::noir) {

		tour4 = make_shared<Tour>(Tour({ 7,8 }, Couleur::noir, "Tour noir D"));

		return tour4;
	}
	else if (tour4 != nullptr && couleur == Couleur::noir) {

		return tour4;
	}

}



Tour::Tour(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {

	cout << "La piece " << this->nom_ << " a ete cree a l'endroit ";
	position.positionNumerotation();
	cout << "\n";

}

bool Tour::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	//Deplacement horizontale
	if (positionActuelle.x == positionApres.x) {
		return true;
	}
	else if (positionActuelle.y == positionApres.y) {
		return true;
	}

	return false;

}

bool Tour::verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec) {
	if (Tour::validationMouvement(position, tableauEchec)) {
		int nCasesDistance = 0;
		bool deplacementHorizontale = true;

		if (positionActuelle.y == position.y) {
			nCasesDistance = abs(this->positionActuelle.x - position.x);
			deplacementHorizontale = false;

		}
		else if (positionActuelle.x == position.x) {
			nCasesDistance = abs(this->positionActuelle.y - position.y);

		}

		int indexY = this->positionActuelle.y;
		int indexX = this->positionActuelle.x;

		bool blocage = true;

		for (int i = 0; i < nCasesDistance; i++) {

			if (deplacementHorizontale) {
				if (position.y - positionActuelle.y < 0) {

					indexY--;

				}
				else {
					indexY++;
				}
			}
			else {
				if (position.x - positionActuelle.x < 0) { indexX--; }
				else { indexX++; }
			}


			if (tableauEchec[indexX][indexY] == nullptr) {


				blocage = false;

			}

			else {


				blocage = true;

			}

			if (blocage == true) {

				if (position.x != indexX || position.y != indexY) {

					mouvementPossible = false;

				}

				return true;
			}

		}

		return false;

	}
}

