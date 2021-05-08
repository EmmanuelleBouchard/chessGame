#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <memory>

#include "Piece.h"
#include "Fou.h"
#include "Ajout.h"


std::shared_ptr<Piece> Fou::Fou::getInstanceFouGauche(Couleur couleur) {

	if (fou1 == nullptr && couleur == Couleur::blanc) {

		fou1 = make_shared<Fou>(Fou({ 0,6 }, Couleur::blanc, "Fou blanc G"));

		return fou1;
	}
	else if (fou1 != nullptr && couleur == Couleur::blanc) {

		return fou1;
	}

	if (fou2 == nullptr && couleur == Couleur::noir) {

		fou2 = make_shared<Fou>(Fou({ 7,3 }, Couleur::noir, "Fou noir G"));

		return fou2;
	}
	else if (fou2 != nullptr && couleur == Couleur::noir) {

		return fou2;
	}

}


std::shared_ptr<Piece> Fou::Fou::getInstanceFouDroite(Couleur couleur) {

	if (fou3 == nullptr && couleur == Couleur::blanc) {

		fou3 = make_shared<Fou>(Fou({ 0,3 }, Couleur::blanc, "Fou blanc D"));

		return fou3;
	}
	else if (fou3 != nullptr && couleur == Couleur::blanc) {

		return fou3;
	}

	if (fou4 == nullptr && couleur == Couleur::noir) {

		fou4 = make_shared<Fou>(Fou({ 7,6 }, Couleur::noir, "Fou noir D"));

		return fou4;
	}
	else if (fou4 != nullptr && couleur == Couleur::noir) {

		return fou4;
	}

}



Fou::Fou::Fou(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {


}

bool Fou::Fou::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	//Deplacement horizontale
	if ((abs(positionApres.x - positionActuelle.x) == (abs(positionApres.y - positionActuelle.y)))) {
		return true;
	}

	return false;

}

bool Fou::Fou::verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec) {
	if (Fou::validationMouvement(position, tableauEchec)) {
		int nCasesDistance = abs(this->positionActuelle.y - position.y);

			int indexY = this->positionActuelle.y;
			int indexX = this->positionActuelle.x;

			bool blocage = true;

			for (int i = 0; i < nCasesDistance; i++) {


				if ((this->positionActuelle.y - position.y) < 0) indexY++;
				else indexY--;

				if ((this->positionActuelle.x - position.x) < 0) indexX++;
				else indexX--;


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

