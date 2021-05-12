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

	friend class Test;
	vector<vector<shared_ptr<Piece>>>  listeTeamBleu;
	vector<vector<shared_ptr<Piece>>>  listeTeamRouge;

	map<string, shared_ptr<Piece>> listePieceBlanche;
	map<string, shared_ptr<Piece>> listePieceNoir;


	~PlateauEchec();

	static unique_ptr<PlateauEchec> getInstancePlateau();

	bool deplacementPiece(shared_ptr<Piece>& piece, Position position, bool test);
	bool getCase(Position position);

	bool mouvementValide(const shared_ptr<Piece>& piece, Position position);
	bool deplacementEchec(shared_ptr<Piece> pieceSelectionneModele, Position positionFinale);
	const shared_ptr<Piece> getPiece(int x, int y);


	void resetGame();
	bool verificationEchecMatPat(bool roiBlanc);
	void promotionPion(int x, int y, shared_ptr<Piece> pion);

	pair<int, int> indexPremiereCaseVide(vector<vector<shared_ptr<Piece>>>  liste, int rangee, int colonne);
	pair<bool, shared_ptr<Piece>> castling(const shared_ptr<Piece>& piece, Position position);

	bool estEchecMat = false;
	bool estEchecPat = false;
	bool deplacementCastling = false;
	bool promotion = false;

private:

	friend class Piece;

	

	vector<vector<shared_ptr<Piece>>>      tableauEchec;
	vector<vector<shared_ptr<Piece>>>      tableauNulle;
	vector<vector<shared_ptr<Piece>>>      listeTemporaire;
	inline static unique_ptr<PlateauEchec> plateau = nullptr;

	PlateauEchec();
	bool roiEchec(bool roiBlanc);
	bool debordementCase(Position position);
	bool situationEchec(shared_ptr<Piece> pieceSelectionnee, Position positionFinale, map<string, shared_ptr<Piece>>& listePieceAttaquante, bool estRoi, bool estPieceAttaquanteNoir);
	bool miseEnEchec(int x, int y, bool estNoir, bool changerPosition, Position positionRoi);


	void initialiserJeux();
	void initialisationPosition(Position position, shared_ptr<Piece> piece);
	void restaurerDeplacement(shared_ptr<Piece> pieceAttaquee, shared_ptr<Piece> pieceSelectionnee, Position positionFinale);
	void eliminationPieceModel(Position position);




};


