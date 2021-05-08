#pragma once
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"

	using namespace std;



	class Roi : public Piece
	{
	public:

		static shared_ptr<Piece> getInstanceRoi(Couleur couleur);
		static void effacerInstanceRoi();


	private:


		inline static shared_ptr<Piece> roi1 = nullptr;

		bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);


		Roi(Position position, Couleur couleur, string nom);

		friend class PlateauEchec;

		inline static shared_ptr<Piece> roi2 = nullptr;

	};





