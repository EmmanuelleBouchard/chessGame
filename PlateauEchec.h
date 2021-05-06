#pragma once
#include "Ajout.h"

#include<iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "Piece.h"
using namespace std;

class PlateauEchec
{

public:
	void transfertListeAttente(shared_ptr<Piece>);
	~PlateauEchec();
	static unique_ptr<PlateauEchec> getInstancePlateau();


	bool deplacementPiece(shared_ptr<Piece>& piece, Position position, bool test);
	bool getCase(Position position);
	const shared_ptr<Piece> getPiece(int x, int y);
	bool mouvementValide(const shared_ptr<Piece>& piece, Position position);
	string mouvementInterditMessage(shared_ptr<Piece> piece, Position positionApres);
	bool miseEnEchec(int x, int y, bool estNoir, bool changerPosition, bool verif, Position positionRoi);

	void eliminationPieceModele(shared_ptr<Piece> pieceDetruite);

	bool deplacementEchec(shared_ptr<Piece> pieceSelectionneModele, Position positionFinale);

	pair<int, int> indexPremiereCaseVide(vector<vector<shared_ptr<Piece>>>  liste, int rangee, int colonne);


	vector<vector<shared_ptr<Piece>>>  listeTeamBleu;
	vector<vector<shared_ptr<Piece>>>  listeTeamRouge;

	map<string, shared_ptr<Piece>> listePieceBlanche;
	map<string, shared_ptr<Piece>> listePieceNoir;
	void liste1();
	void liste2();


	void resetGame();

	void transfertListePieceEliminee(Position positionFinale);



private:



	friend class Piece;


	PlateauEchec();
	bool debordementCase(Position position);
	void initialiserJeux();
	void initialisationPosition(Position position, shared_ptr<Piece> piece);
	void restaurerDeplacement(shared_ptr<Piece> pieceAttaquee, shared_ptr<Piece> pieceSelectionnee, Position positionFinale);

	vector<vector<shared_ptr<Piece>>> tableauEchec;
	vector<vector<shared_ptr<Piece>>> tableauNulle;
	vector<vector<shared_ptr<Piece>>> listeTemporaire;

	inline static unique_ptr<PlateauEchec> plateau = nullptr;
};

