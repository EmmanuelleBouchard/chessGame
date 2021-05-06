#pragma once
#include "Piece.h"
#include <iostream>
#include "Ajout.h"
#include "PlateauEchec.h"

	using namespace std;




	class Fou : virtual public Piece {
	public:

		static shared_ptr<Piece> getInstanceFouGauche(Couleur couleur);
		static shared_ptr<Piece> getInstanceFouDroite(Couleur couleur);
		

	protected:
		Fou() = default;
		virtual bool verificationAutrePiece(Position position, vector<vector<shared_ptr<Piece>>>& tableauEchec);
		virtual bool validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec);
	private:

		
	


		Fou(Position position, Couleur couleur, string nom);

		friend class PlateauEchec;

		inline static shared_ptr<Piece> fou1 = nullptr;
		inline static shared_ptr<Piece> fou2 = nullptr;

		inline static shared_ptr<Piece> fou3 = nullptr ;
		inline static shared_ptr<Piece> fou4 = nullptr;


	};



