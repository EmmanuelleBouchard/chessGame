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


}

bool Pion::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {

	bool deplacementDeuxCaseAvant = 0;
	bool positionXValide = 0;
	int positionXSuivante = 0;
	int positionXDeuxCase = 0;
	bool promotion = 0;

	if (this->couleur_ == Couleur::blanc) {

		deplacementDeuxCaseAvant = (positionActuelle.y == positionApres.y) and (positionActuelle.x + 2 == positionApres.x) and debut;
		positionXValide = (positionActuelle.x + 1 == positionApres.x) or deplacementDeuxCaseAvant;
		positionXSuivante = positionActuelle.x + 1;
		promotion = positionApres.x == 8;
		positionXDeuxCase = 3;
	}
	else if (this->couleur_ == Couleur::noir) {
		deplacementDeuxCaseAvant = (positionActuelle.y == positionApres.y) and (positionActuelle.x - 2 == positionApres.x) and debut;
		positionXValide = (positionActuelle.x - 1 == positionApres.x) or deplacementDeuxCaseAvant;
		positionXSuivante = positionActuelle.x - 1;
		promotion = positionApres.x == 0;
		positionXDeuxCase = 4;
	}

	bool positionYValide = abs(positionActuelle.y - positionApres.y) <= 1;

		
		if (positionXValide and positionYValide) {

			shared_ptr<Piece> pieceGauche = nullptr;
			shared_ptr<Piece> pieceDroite = nullptr;
			shared_ptr<Piece> pieceMilieu = nullptr;
			shared_ptr<Piece> pieceMilieuDeuxCase = nullptr;
			bool derniereCase = false;
		
			if (positionActuelle.y > 1 and positionActuelle.y < 8) {
				pieceGauche = tableauEchec[positionXSuivante][positionActuelle.y - 1];
				pieceDroite = tableauEchec[positionXSuivante][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 1) {
				pieceDroite = tableauEchec[positionXSuivante][positionActuelle.y + 1];
			}
			else if (positionActuelle.y == 8) {
				pieceGauche = tableauEchec[positionXSuivante][positionActuelle.y - 1];
			}

			if (promotion == false) {
				pieceMilieu = tableauEchec[positionXSuivante][positionActuelle.y];
				pieceMilieuDeuxCase = tableauEchec[positionXDeuxCase][positionActuelle.y];
			}

			bool deplacementGauche = positionApres.y - positionActuelle.y < 0;
			bool deplacementMilieu = positionApres.y - positionActuelle.y == 0;
			bool deplacementDroite = positionApres.y - positionActuelle.y > 0;


			if (deplacementGauche) {

				if (pieceGauche == nullptr) {
					return false;
				}
				return true;
			}

		
			else if (deplacementMilieu) {

				if (deplacementDeuxCaseAvant) {
					if (pieceMilieu != nullptr or pieceMilieuDeuxCase != nullptr) {
						return false;
					}
					
					return true;
				}
				else if (promotion) {

				//À modifier pour la derniere case (reviving)
					return true;
				}
				else if (debut == false and ((abs(positionApres.x - positionActuelle.x) == 2))) {
					return false;
				}
				else if (pieceMilieu != nullptr) {
					return false;
				}

				return true;
			}

			
			else if (deplacementDroite) {

				if (pieceDroite == nullptr) {
					return false;
				}
				return true;
			}



		}

	return false;
}
