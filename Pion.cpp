#include "Pion.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iostream>
#include <memory>

#include "Piece.h"
#include "Ajout.h"






Pion::Pion(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {
	estPion = true;
	cout << "La piece " << this->nom_ << " a ete cree a l'endroit ";
	position.positionNumerotation();
	cout << "\n";

}

bool Pion::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	//Deplacement horizontale
	if (couleur_ == Couleur::blanc) {
		
		bool positionXValide = (positionActuelle.x + 1 == positionApres.x) or ((positionActuelle.x + 2 == positionApres.x) and debut);
		if (positionXValide and abs(positionActuelle.y - positionApres.y) <= 1) {
			shared_ptr<Piece> pieceGauche = nullptr;
			shared_ptr<Piece> pieceDroite = nullptr;
			shared_ptr<Piece> pieceMilieu = nullptr;
			bool derniereCase = false;

			if (positionActuelle.y > 1 and positionActuelle.y < 8) {
				pieceGauche = tableauEchec[positionActuelle.x + 1][positionActuelle.y - 1];
				pieceDroite = tableauEchec[positionActuelle.x + 1][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 1) {
				pieceDroite = tableauEchec[positionActuelle.x + 1][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 8) {
				pieceGauche = tableauEchec[positionActuelle.x + 1][positionActuelle.y - 1];
			}
			
			if (positionApres.x < 8) {
				pieceMilieu = tableauEchec[positionActuelle.x + 1][positionActuelle.y];
			}
			else {
				derniereCase = true;
			}
	

			if (positionApres.y - positionActuelle.y < 0) {
				if (pieceGauche== nullptr) {
					return false;
				}
				return true;
			}
			else if (positionApres.y - positionActuelle.y == 0) {
				if (debut) {
					if ((positionApres.x - positionActuelle.x == 2) and (positionActuelle.y == positionApres.y)) {
						return true;
					}
				}if (derniereCase) {
					return false;
				}if (debut == false and ((positionApres.x - positionActuelle.x == 2))) {
					return false;
				}
				if (pieceMilieu != nullptr) {
				return false;
			}

				return true;
			}
			else if (positionApres.y - positionActuelle.y > 0) {
				if (pieceDroite == nullptr) {
					return false;
				}
				return true;
			}


			
		}
	}
	if (couleur_ == Couleur::noir) {
		bool derniereCase = false;
		bool positionXValide = (positionActuelle.x - 1 == positionApres.x) or ((positionActuelle.x - 2 == positionApres.x) and debut);
		if (positionXValide and abs(positionActuelle.y - positionApres.y) <= 1) {
			shared_ptr<Piece> pieceGauche = nullptr;
			shared_ptr<Piece> pieceDroite = nullptr;
			shared_ptr<Piece> pieceMilieu = nullptr;

			if(positionActuelle.y > 1 and positionActuelle.y < 8) {
				pieceGauche = tableauEchec[positionActuelle.x - 1][positionActuelle.y - 1];
				pieceDroite = tableauEchec[positionActuelle.x - 1][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 1) {
				pieceDroite = tableauEchec[positionActuelle.x - 1][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 8) {
				pieceGauche = tableauEchec[positionActuelle.x - 1][positionActuelle.y - 1];
			}

			//changer
			if (positionApres.x > 0) {
				pieceMilieu = tableauEchec[positionActuelle.x - 1][positionActuelle.y];
			}
			else {
				derniereCase = true;
			}

			if (positionApres.y - positionActuelle.y < 0) {
				if (pieceGauche == nullptr) {
					return false;
				}
				return true;
			}
			else if (positionApres.y - positionActuelle.y == 0) {

				if (debut) {
					if ((positionApres.x - positionActuelle.x == -2) and (positionActuelle.y == positionApres.y)) {
						return true;
					}
				}
				if (derniereCase) {
					return false;
				}
				if (debut == false and ((positionApres.x - positionActuelle.x == -2))) {
				return false;
				}if (pieceMilieu != nullptr) {
					return false;
			}

				return true;
			}
			else if (positionApres.y - positionActuelle.y > 0) {
				if (pieceDroite == nullptr) {
					return false;
				}
				return true;
			}


		}
	}

	return false;

}
