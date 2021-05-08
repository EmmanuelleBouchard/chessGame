#include "PlateauEchec.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include "Roi.h"
#include "Fou.h"
#include "Tour.h"
#include "Cavalier.h"
#include "Reine.h"
#include "Pion.h"


void  PlateauEchec::liste1() {

	this->tableauEchec[0][3]->positionActuelle = { 2,3 };

	this->tableauEchec[2][3] = tableauEchec[0][3];
	this->tableauEchec[0][3] = nullptr;

	//	this->listePieceBlanche[tableauEchec[1][3]->getNom()] = tableauEchec[1][3];

}
void  PlateauEchec::liste2() {
	this->tableauEchec[7][7]->positionActuelle = { 5,7 };

	this->tableauEchec[5][7] = tableauEchec[7][7];
	this->tableauEchec[7][7] = nullptr;

}

string PlateauEchec::mouvementInterditMessage(shared_ptr<Piece> piece, Position positionApres) {

	return "Le mouvement n'est pas permis, vous essayez de deplacer le " + piece->getNom() + " de " +
		piece->positionActuelle.positionNumerotation() + " vers la case " + positionApres.positionNumerotation();

}
void PlateauEchec::eliminationPieceModele(shared_ptr<Piece> pieceDetruire) {

	if (pieceDetruire->getCouleur() == Couleur::noir) {
		listePieceNoir.erase(pieceDetruire->getNom());
	}
	else if (pieceDetruire->getCouleur() == Couleur::blanc) {
		listePieceBlanche.erase(pieceDetruire->getNom());
	}

}

unique_ptr<PlateauEchec> PlateauEchec::getInstancePlateau() {

	if (plateau == nullptr)
		plateau = make_unique<PlateauEchec>(PlateauEchec());

	return move(plateau);
}


bool PlateauEchec::debordementCase(Position position) {
	if ((position.x < 0 || position.x > 7) && (position.y < 1 || position.y >8)) {
		cout << "Depassement du jeu d'echecs!" << endl;
		return true;
	}

	return false;

};

const shared_ptr<Piece> PlateauEchec::getPiece(int x, int y) {

	return tableauEchec[x][y];
}

bool PlateauEchec::mouvementValide(const shared_ptr<Piece>& piece, Position position) {

	if (debordementCase(position))
		return false;


		if (piece->getPositionActuelle().positionNumerotation() == position.positionNumerotation()) {
			return false;
		}

		if (piece->validationMouvement(position, tableauEchec)) {

			auto autrePiece = tableauEchec[position.x][position.y];

			if ((piece->verificationAutrePiece(position, tableauEchec))) {
				if ((piece->pareilCouleur(autrePiece))) {
					piece->mouvementPossible = true;
					return false;
				}
				if (piece->mouvementPossible == false) {

					piece->mouvementPossible = true;
					return false;
				}
			}

			return true;

		}
	

	return false;
	
}

pair<int, int> PlateauEchec::indexPremiereCaseVide(vector<vector<shared_ptr<Piece>>>  liste,int rangee,int colonne) {
	for (int i = 0; i < rangee; i++) {
		for (int j = 0; j < colonne; j++) {
			if (liste[i][j] == nullptr) {
				return make_pair(i,j);
			}
		}
	}
	return make_pair(-1, -1);
}
//A faire qqch
bool PlateauEchec::deplacementPiece(shared_ptr<Piece>& piece, Position position, bool test) {

	Position positionAncien = piece->positionActuelle;
	auto autrePiece = tableauEchec[position.x][position.y];

	if (auto && pion = dynamic_cast<Pion*>(piece.get()) and test == false) {
		piece->debut = false;
	}

	//Si on attaque, je met la pi;ece bouff� dans ma liste black list
	if (tableauEchec[position.x][position.y] != nullptr and test == false) {

		auto pieceAttaquee = tableauEchec[position.x][position.y];
		bool estPieceBlanche = pieceAttaquee->getCouleur() == Couleur::blanc;

		if (estPieceBlanche) {
			listePieceBlanche.erase(pieceAttaquee->getNom());
			bool continuer = true;
			auto index = indexPremiereCaseVide(listeTeamBleu, 8, 2);
			if (index.first != -1 or index.second != -1) {

				listeTeamBleu[index.first][index.second] = pieceAttaquee;
				pieceAttaquee->positionActuelle = { index.first,index.second };
				continuer = false;

			}


			
		}
		else {
			listePieceNoir.erase(pieceAttaquee->getNom());
			bool continuer = true;


			auto index = indexPremiereCaseVide(listeTeamRouge, 8, 2);
			if (index.first != -1 or index.second != -1) {

				listeTeamRouge[index.first][index.second] = pieceAttaquee;
				pieceAttaquee->positionActuelle = { index.first,index.second };
				continuer = false;

			}

		}

		

	}

	tableauEchec[positionAncien.x][positionAncien.y] = nullptr;
	tableauEchec[position.x][position.y] = piece;

	piece->positionActuelle = position;

	return true;

}

bool PlateauEchec::miseEnEchec(int x, int y, bool estPieceAttaquanteNoir, bool estRoi, Position positionRoi)
{

	auto pieceAttaquante = tableauEchec[x][y];
	/*	
	* 
	* estRoi == false
	* Si la pi�ce s�lectionn�  n'est pas un Roi, alors on v�rifie s'il y a un mouvement possible entre la pieceAttaquante (pi�ce s�lectionn� ) et le Roi adverse (positionRoi)
	* 
	* estRoi == true
	* Si la pi�ce s�lectionn� est un Roi, alors on v�rifie s'il y a un mouvement possible avec la piece Attaquante( le Roi lui-m�me ) et sa futur position (positionRoi)
	* 
	*/


	if (estPieceAttaquanteNoir) {

		if (estRoi == false) {
			positionRoi = Roi::roi1->getPositionActuelle();
		}


		if (mouvementValide(pieceAttaquante, positionRoi)) {

			return true;
		}
	
	}
	else {

		if (estRoi == false) {
			positionRoi = Roi::roi2->getPositionActuelle();
		}
		if (mouvementValide(pieceAttaquante, positionRoi)) {

			return true;


		}

	

	}


	return false;
}




bool PlateauEchec::deplacementEchec(shared_ptr<Piece> pieceSelectionnee, Position positionFinale) {

	string   nomPieceSelectionnee = pieceSelectionnee->getNom();
	bool     estRoi = false;
	bool     estPieceAttaquanteNoir = pieceSelectionnee->getCouleur() == Couleur::blanc;

	map<string, shared_ptr<Piece>> listePieceAttaquante;
	


	if (estPieceAttaquanteNoir == true) {
		listePieceAttaquante = listePieceNoir;
	}
	else if (estPieceAttaquanteNoir == false) {
		listePieceAttaquante = listePieceBlanche;
	}

	if (nomPieceSelectionnee == "Roi blanc" || nomPieceSelectionnee == "Roi noir")
		estRoi = true;

	//Si la pi�ce s�lectionn�e est le Roi, on v�rifie si son d�placement va lui causer un �chec
	if (estRoi) {

			//On va g�rer toute mouvement des pi�ce attaquante par rapport au roi sauf les pions (car le mouvement attaquant du pion est sp�ciale)
			for (auto&& pieceAttaquante : listePieceAttaquante) {
				bool estEchec = miseEnEchec(pieceAttaquante.second->getPositionActuelle().x, pieceAttaquante.second->getPositionActuelle().y, estPieceAttaquanteNoir, estRoi, positionFinale);
				bool estPion = pieceAttaquante.second->estPion;
				
				if (estEchec and estPion == false) {
					return true;
				}
			}



	
	}

	//Si la pi�ce s�lectionn�e est une autre pi�ce, on v�rifie si son d�placement va causer l'�chec de son propre roi ou
	//Dans le cas o� la pi�ce s�lectionn�e est un roi et que la pi�ce attaquante est un pion, on v�rifie que le d�placement du roi le mettra en �chec

		if (situationEchec(pieceSelectionnee,  positionFinale, listePieceAttaquante,  estRoi, estPieceAttaquanteNoir)) {
			return true;
		}
	

	return false;
}


bool PlateauEchec::situationEchec(shared_ptr<Piece> pieceSelectionnee, Position positionFinale, map<string, shared_ptr<Piece>>& listePieceAttaquante, bool estRoi, bool estPieceAttaquanteNoir) {
	
	Position positionPieceSelectionnee = pieceSelectionnee->positionActuelle;
	shared_ptr<Piece> pieceAttaquee = tableauEchec[positionFinale.x][positionFinale.y];

	if (mouvementValide(pieceSelectionnee, positionFinale)) {

		//D�place la pi�ce s�lectionn�e � l'endroit voulu afin de v�rifi� si son d�placement va caus� un post �chec
		deplacementPiece(pieceSelectionnee, positionFinale, true);
		pieceSelectionnee->positionActuelle = positionFinale;

		for (auto&& pieceAttaquante : listePieceAttaquante) {

			bool mouvementRoiPion = pieceAttaquante.second->estPion and estRoi;
			bool estEchec = miseEnEchec(pieceAttaquante.second->getPositionActuelle().x, pieceAttaquante.second->getPositionActuelle().y, estPieceAttaquanteNoir, estRoi,positionFinale);

			if (estEchec and (mouvementRoiPion or estRoi == false )) {
				restaurerDeplacement(pieceAttaquee, pieceSelectionnee, positionPieceSelectionnee);
				return true;
			}
			
		
		}


		restaurerDeplacement(pieceAttaquee, pieceSelectionnee, positionPieceSelectionnee);
	}
	return false;

}

void PlateauEchec::restaurerDeplacement(shared_ptr<Piece> pieceAttaquee, shared_ptr<Piece> pieceSelectionnee, Position positionAvant ) {
	Position positionPieceSelectionnee = pieceSelectionnee->positionActuelle;

	deplacementPiece(pieceSelectionnee, positionAvant, true);
	tableauEchec[positionPieceSelectionnee.x][positionPieceSelectionnee.y] = pieceAttaquee;
	pieceSelectionnee->positionActuelle = positionAvant;
}


PlateauEchec::PlateauEchec() {

	tableauEchec.resize(8);
	tableauNulle.resize(8);
	listeTeamBleu.resize(8);
	listeTeamRouge.resize(8);
	listeTemporaire.resize(8);
		
	for (int i = 0; i < 8; ++i) {
		tableauEchec[i].resize(9);
		tableauNulle[i].resize(9);
	}

	tableauEchec.resize(8);
	tableauNulle.resize(8);

	for (int i = 0; i < 8; ++i) {
		listeTeamBleu[i].resize(2);
		listeTeamRouge[i].resize(2);
		listeTemporaire[i].resize(2);
	}

	initialiserJeux();

	cout << "Le plateau d'echecs a ete construit!" << endl;

}


bool PlateauEchec::getCase(Position position) {

	cout << "Nom : " << tableauEchec[position.x][position.y]->getNom() << " | " << "Position : ";
	if (tableauEchec[position.x][position.y] != nullptr) {
		tableauEchec[position.x][position.y]->getPositionActuelle();
		return true;
	}
	else {
		position.positionNumerotation();
		cout << "\n";
		return false;
	}
}

void PlateauEchec::initialiserJeux() {
	tableauEchec.clear();
	tableauEchec = tableauNulle;
	listeTeamBleu = listeTemporaire;
	listeTeamRouge = listeTemporaire;


	//Roi
	tableauEchec[0][5] = Roi::getInstanceRoi(Couleur::blanc);
	tableauEchec[7][5] = Roi::getInstanceRoi(Couleur::noir);

	listePieceBlanche[Roi::roi1->getNom()] = Roi::roi1;
	listePieceNoir[Roi::roi2->getNom()] = Roi::roi2;

	//Reine
	tableauEchec[0][4] = Reine::getInstanceReine(Couleur::blanc);
	tableauEchec[7][4] = Reine::getInstanceReine(Couleur::noir);

	listePieceBlanche[Reine::reine1->getNom()] = Reine::reine1;
	listePieceNoir[Reine::reine2->getNom()] = Reine::reine2;

	//Cavalier de gauche

	tableauEchec[0][7] = Cavalier::getInstanceCavalierGauche(Couleur::blanc);
	listePieceBlanche[Cavalier::cavalier1->getNom()] = Cavalier::cavalier1;

	tableauEchec[7][2] = Cavalier::getInstanceCavalierGauche(Couleur::noir);
	listePieceNoir[Cavalier::cavalier2->getNom()] = Cavalier::cavalier2;


	//Cavalier de droite

	tableauEchec[0][2] = Cavalier::getInstanceCavalierDroite(Couleur::blanc);
	listePieceBlanche[Cavalier::cavalier3->getNom()] = Cavalier::cavalier3;


	tableauEchec[7][7] = Cavalier::getInstanceCavalierDroite(Couleur::noir);
	listePieceNoir[Cavalier::cavalier4->getNom()] = Cavalier::cavalier4;


	//Fou de gauche

	tableauEchec[0][6] = Fou::getInstanceFouGauche(Couleur::blanc);
	listePieceBlanche[Fou::fou1->getNom()] = Fou::fou1;


	tableauEchec[7][3] = Fou::getInstanceFouGauche(Couleur::noir);
	listePieceNoir[Fou::fou2->getNom()] = Fou::fou2;


	//Fou de droite

	tableauEchec[0][3] = Fou::getInstanceFouDroite(Couleur::blanc);
	listePieceBlanche[Fou::fou3->getNom()] = Fou::fou3;

	tableauEchec[7][6] = Fou::getInstanceFouDroite(Couleur::noir);
	listePieceNoir[Fou::fou4->getNom()] = Fou::fou4;

	//Tour gauche
	tableauEchec[0][8] = Tour::getInstanceTourGauche(Couleur::blanc);
	listePieceBlanche[Tour::tour1->getNom()] = Tour::tour1;

	tableauEchec[7][1] = Tour::getInstanceTourGauche(Couleur::noir);
	listePieceNoir[Tour::tour2->getNom()] = Tour::tour2;


	//Tour droite
	tableauEchec[0][1] = Tour::getInstanceTourDroite(Couleur::blanc);
	listePieceBlanche[Tour::tour3->getNom()] = Tour::tour3;

	tableauEchec[7][8] =Tour::getInstanceTourDroite(Couleur::noir);
	listePieceNoir[Tour::tour4->getNom()] = Tour::tour4;

	//Pion blanc
	string nom = "Pion blanc ";

	for (int i = 1; i <= 8; i++) {
		nom += to_string(i);
		tableauEchec[1][i] = make_shared<Pion>((Pion({ 1,i }, Couleur::blanc, nom)));
		listePieceBlanche[nom] = tableauEchec[1][i];
		nom = "Pion blanc ";
	}

	//Pion noir

	nom = "Pion noir ";
	for (int i = 1; i <= 8; i++) {
		nom += to_string(i);
		tableauEchec[6][i] = make_shared<Pion>((Pion({ 6,i }, Couleur::noir, nom)));
		listePieceNoir[nom] = tableauEchec[6][i];
		nom = "Pion noir ";
	}

}

PlateauEchec::~PlateauEchec() {

	cout << "Le plateau de jeu a ete detruit!" << endl;
}

void PlateauEchec::initialisationPosition(Position position, shared_ptr<Piece> piece) {
	piece->positionActuelle = position;
}

void PlateauEchec::resetGame() {

	initialisationPosition({ 0,6 }, Fou::fou1);
	initialisationPosition({ 7,3 }, Fou::fou2);
	initialisationPosition({ 0,3 }, Fou::fou3);
	initialisationPosition({ 7,6 }, Fou::fou4);



	initialisationPosition({ 0,8 }, Tour::tour1);
	initialisationPosition({ 7,1 }, Tour::tour2);
	initialisationPosition({ 0,1 }, Tour::tour3);
	initialisationPosition({ 7,8 }, Tour::tour4);

	initialisationPosition({ 0,5 }, Roi::roi1);
	initialisationPosition({ 7,5 }, Roi::Roi::roi2);

	initialisationPosition({ 0,4 }, Reine::reine1);
	initialisationPosition({ 7,4 }, Reine::reine2);

	initialisationPosition({ 0,7 }, Cavalier::cavalier1);
	initialisationPosition({ 7,2 }, Cavalier::cavalier2);
	initialisationPosition({ 0,2 }, Cavalier::cavalier3);
	initialisationPosition({ 7,7 }, Cavalier::cavalier4);

	initialisationPosition({ 0,8 }, Tour::tour1);
	initialisationPosition({ 7,1 }, Tour::tour2);
	initialisationPosition({ 0,1 }, Tour::tour3);
	initialisationPosition({ 7,8 }, Tour::tour4);



	listePieceBlanche.clear();
	listePieceNoir.clear();
	listeTeamBleu.clear();
	listeTeamRouge.clear();
	tableauEchec.clear();

	initialiserJeux();
}


