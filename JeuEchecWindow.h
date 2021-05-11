#pragma once
#include <QMainWindow>
#include <QIcon>
#include "Ajout.h"
#include "Piece.h"
#include "PlateauEchec.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Tour.h"
#include "Reine.h"
#include <qtablewidget.h>
#include  <QLabel>
#include <QMediaPlayer>

//#include "debogage_memoire.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class JeuEchecWindow; }
QT_END_NAMESPACE



	using namespace std;



	class JeuEchecWindow : public QMainWindow
	{
		Q_OBJECT

	public:

		JeuEchecWindow(QWidget* parent = nullptr);
		~JeuEchecWindow();
	
		Ui::JeuEchecWindow* ui;


	public slots:

		void deplacementPiece(int x, int y);
		void resizeEvent(QResizeEvent*);
		void remettreJeuxInitiale();
		void MakeActive();
		void liste1();
		void liste2();
		void promotionNoir(int x, int y);
		void promotionBlanc(int x, int y);
		void promotion(int x, int y, bool listeBlanche);


	private:
		void eliminationPieceVue(shared_ptr<Piece> pieceAttaquante,shared_ptr<Piece> pieceAttaquee);
		bool caseNoir(Position position);
		void coloriageCaseValide(Position positionPieceSelectionne);
		void remettreCouleurCaseAvant();
		void initialisationFenetre();
		void mouvementValide(shared_ptr<Piece> piece, Position position);
		void messageMouvementInvalide(shared_ptr<Piece> piece, Position position,bool echec);
		
		void effetMusiqueDeplacement();
		string listeChoisi = "";
			
		Position positionPieceSelectionne;
		bool premierClic = true;
		bool tourBlanc = true;
		shared_ptr<PlateauEchec> plateau = PlateauEchec::getInstancePlateau();
		vector<Position> listeCaseColoriee;
		QMediaPlayer* musiqueDeplacement = new QMediaPlayer();
		shared_ptr<Piece> pieceSelectionne = nullptr;
		
		

	};

