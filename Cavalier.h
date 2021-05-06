#pragma once
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"


	using namespace std;



	class Cavalier : public Piece {

	public:

		static shared_ptr<Piece> getInstanceCavalierGauche(Couleur couleur);
		static shared_ptr<Piece> getInstanceCavalierDroite(Couleur couleur);


	private:

		bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);


		Cavalier(Position position, Couleur couleur, string nom);

		friend class PlateauEchec;
		inline static shared_ptr<Piece> cavalier1 = nullptr;
		inline static shared_ptr<Piece> cavalier2 = nullptr;

		inline static shared_ptr<Piece> cavalier3 = nullptr;
		inline static shared_ptr<Piece> cavalier4 = nullptr;


	};
