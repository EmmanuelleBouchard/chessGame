#pragma once
#include "Ajout.h"

#include<iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>


	using namespace std;
	

	
	
	class Piece {

	public:

		Piece();
		Piece(Position position, Couleur couleur, string nom);

		virtual  bool verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec);
		virtual bool validationMouvement(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec);

		string getNom();
		Couleur getCouleur();
		Position getPositionActuelle();
		bool pareilCouleur(shared_ptr<Piece> piece);




	protected:

		//friend class Plateau;
		friend class PlateauEchec;
		Position positionActuelle;
		Couleur couleur_;
		string nom_;
		bool mouvementPossible = true;

		bool debut = true;
		bool estPion = false;



	private:


	};
