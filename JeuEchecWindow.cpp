#include <iostream>
#include <string>

//#include "ui_PlateauEchec.h"
#include <QTableWidget>
//#include "ui_PlateauEchec.h"
#include <QMessageBox>
#include <QPixmap>
#include <qscreen.h>
#include <QLabel>

#include <QMediaPlayer>
#include "JeuEchecWindow.h"

#include "ui_PlateauEchec.h"


JeuEchecWindow::JeuEchecWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::JeuEchecWindow)
{
	ui->setupUi(this);

	connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(deplacementPiece(int, int)));
	connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(remettreJeuxInitiale()));


	initialisationFenetre();


}




void JeuEchecWindow::initialisationFenetre() {
	ui->gridLayout->setAlignment(ui->tableWidget, Qt::AlignCenter);

	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->verticalHeader()->setFixedWidth(25);
	ui->tableWidget->horizontalHeader()->setFixedHeight(35);

	int tailleHorizontaleListeBlanche = ui->listeBlanche->horizontalHeader()->length();
	auto tailleVerticaleListeBlanche = ui->listeBlanche->verticalHeader()->length();

	ui->listeBlanche->setMaximumWidth(tailleHorizontaleListeBlanche);
	ui->listeBlanche->setMaximumHeight(tailleVerticaleListeBlanche);

	auto tailleHorizontaleListeNoire = ui->listeNoire->horizontalHeader()->length();
	auto tailleVerticaleListeNoire = ui->listeNoire->verticalHeader()->length();

	ui->listeNoire->setMaximumWidth(tailleHorizontaleListeNoire);
	ui->listeNoire->setMaximumHeight(tailleVerticaleListeNoire);

	ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
	ui->resetButton->setStyleSheet("background : rgba(94,94,94)");



	ui->listeBlanche->setIconSize(QSize(25, 25));
	ui->listeNoire->setIconSize(QSize(25, 25));

	ui->tourRole->setText("Tour : BLANC");
	musiqueDeplacement->setMedia(QUrl("qrc:/Ressource/sound/351518__mh2o__chess-move-on-alabaster.wav"));
	effetMusiqueDeplacement();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			QTableWidgetItem* itemBlanc = new QTableWidgetItem;
			itemBlanc->setIcon(QIcon());
			QTableWidgetItem* itemNoir = new QTableWidgetItem;
			itemNoir->setIcon(QIcon());
			ui->listeBlanche->setItem(i, j, itemBlanc);
			ui->listeNoire->setItem(i, j, itemNoir);
		}
	}



}


void JeuEchecWindow::MakeActive() {
	raise();
	this->show();
	this->activateWindow();
	this->raise();
}

void  JeuEchecWindow::liste1() {
	auto image = ui->tableWidget->item(0, 2)->icon();
	ui->tableWidget->item(2, 2)->setIcon(image);
	ui->tableWidget->item(0, 2)->setIcon(QIcon());

	plateau->liste1();


}
void JeuEchecWindow::liste2() {

	auto image = ui->tableWidget->item(7, 6)->icon();
	ui->tableWidget->item(5, 6)->setIcon(image);
	ui->tableWidget->item(7, 6)->setIcon(QIcon());

	plateau->liste2();

}
//Augmenter la taille des images des pièces en fonction de la taille de la fenêtre
void JeuEchecWindow::resizeEvent(QResizeEvent* event)
{
	cout << "Height " << this->size().height() << endl;
	cout << "Width" << this->size().width() << endl;

	int tailleHorizontaleTableWidget = ui->tableWidget->horizontalHeader()->sectionSize(0);
	int tailleVerticaleTableWidget = ui->tableWidget->verticalHeader()->sectionSize(0);
	int nouvelleTailleHorizontale = (25 * tailleHorizontaleTableWidget) / 30;


	ui->tableWidget->setIconSize(QSize(nouvelleTailleHorizontale, tailleVerticaleTableWidget));
	QMainWindow::resizeEvent(event);
	

}

bool JeuEchecWindow::caseNoir(Position position) {
	if (position.x % 2 == 0) {
		if (position.y % 2 == 0) {

			return true;
		}
		else {

			return false;

		}
	}
	else {
		if (position.y % 2 == 0) {

			return false;

		}
		else {

			return true;

		}
	}

}

void JeuEchecWindow::coloriageCaseValide(Position positionPieceSelectionnee) {

	int range = ui->tableWidget->rowCount();
	int colonne = ui->tableWidget->columnCount();
	QColor couleur;


	for (int i = 0; i < range; i++) {
		for (int j = 0; j < colonne; j++) {
			if(i == 5 and j == 7){
				cout << "a";
			}
			if ((i != positionPieceSelectionnee.x || positionPieceSelectionnee.y != j)) {
				
				auto piece = plateau->getPiece(positionPieceSelectionnee.x, positionPieceSelectionnee.y + 1);

				if(plateau->mouvementValide(piece, { i,j + 1 }))

				if (plateau->mouvementValide(piece, { i,j + 1 }) and plateau->deplacementEchec(piece, { i,j + 1 }) == false) {
					
					listeCaseColoriee.push_back({ i,j });

					QLinearGradient linearGrad(QPointF(0, 0), QPointF(50, 50));

					if (caseNoir({ i,j })) {
						if (plateau->getPiece(positionPieceSelectionnee.x, positionPieceSelectionnee.y + 1)->getCouleur() == Couleur::noir) {
							//Bleu case Noir
							couleur = QColor(0, 50, 78);
						}
						else {

							//Rouge case noir
							couleur = QColor(110, 0, 0);

						}

					}
					else {
						if (plateau->getPiece(positionPieceSelectionnee.x, positionPieceSelectionnee.y + 1)->getCouleur() == Couleur::noir) {
							//Bleu case Blanche

							couleur = QColor(101, 178, 255);
						}
						else {

							//Rouge case Blanche
							couleur = QColor(255, 92, 92);

						}

					}

					ui->tableWidget->item(i, j)->setBackground(couleur);
				}
				
			}
		}
	}
}


void JeuEchecWindow::remettreCouleurCaseAvant() {

	for (auto position : listeCaseColoriee) {

		if (caseNoir(position)) {
			QBrush brush(QColor(0, 0, 0, 255));
			ui->tableWidget->item(position.x, position.y)->setBackground(brush);
		}
		else {
			QBrush brush(QColor(255, 255, 255, 255));
			ui->tableWidget->item(position.x, position.y)->setBackground(brush);
		}

	}
}

void JeuEchecWindow::remettreJeuxInitiale() {
	if (premierClic == false) {
		remettreCouleurCaseAvant();
		listeCaseColoriee.clear();
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			if (plateau->listeTeamBleu[i][j] != nullptr) {
				auto item = ui->listeBlanche->item(i, j);
				item->setIcon(QIcon());
				
			}
			if (plateau->listeTeamRouge[i][j] != nullptr) {
				auto item = ui->listeNoire->item(i, j);
				item->setIcon(QIcon());
			}
		}
	}

	for (auto&& piece : plateau->listePieceBlanche) {
		auto item = ui->tableWidget->item(piece.second->getPositionActuelle().x, piece.second->getPositionActuelle().y-1);
		item->setIcon(QIcon());
	}

	for (auto&& piece : plateau->listePieceNoir) {
		auto item = ui->tableWidget->item(piece.second->getPositionActuelle().x, piece.second->getPositionActuelle().y-1);
		item->setIcon(QIcon());
	}


	plateau->resetGame();
	tourBlanc = true;
	premierClic = true;
	ui->tourRole->setText("Tour : BLANC");

	ui->tableWidget->item(0, 0)->setIcon(QIcon(":/Ressource/image/rook1.png"));
	ui->tableWidget->item(0, 1)->setIcon(QIcon(":/Ressource/image/cavalierBlanc.png"));
	ui->tableWidget->item(0, 2)->setIcon(QIcon(":/Ressource/image/fouBlanc.png"));
	ui->tableWidget->item(0, 3)->setIcon(QIcon(":/Ressource/image/queen1.png"));
	ui->tableWidget->item(0, 4)->setIcon(QIcon(":/Ressource/image/roiBlanc.png"));
	ui->tableWidget->item(0, 5)->setIcon(QIcon(":/Ressource/image/fouBlanc.png"));
	ui->tableWidget->item(0, 6)->setIcon(QIcon(":/Ressource/image/cavalierBlanc.png"));
	ui->tableWidget->item(0, 7)->setIcon(QIcon(":/Ressource/image/rook1.png"));

	ui->tableWidget->item(7, 0)->setIcon(QIcon(":/Ressource/image/rook.png"));
	ui->tableWidget->item(7, 1)->setIcon(QIcon(":/Ressource/image/cavalierNoir.png"));
	ui->tableWidget->item(7, 2)->setIcon(QIcon(":/Ressource/image/fouNoir.png"));
	ui->tableWidget->item(7, 3)->setIcon(QIcon(":/Ressource/image/queen.png"));
	ui->tableWidget->item(7, 4)->setIcon(QIcon(":/Ressource/image/roiNoir.png"));
	ui->tableWidget->item(7, 5)->setIcon(QIcon(":/Ressource/image/fouNoir.png"));
	ui->tableWidget->item(7, 6)->setIcon(QIcon(":/Ressource/image/cavalierNoir.png"));
	ui->tableWidget->item(7, 7)->setIcon(QIcon(":/Ressource/image/rook.png"));


	for (int i = 0; i < 8; i++) {
		ui->tableWidget->item(1, i)->setIcon(QIcon(":/Ressource/image/pawn1.png"));
		ui->tableWidget->item(6, i)->setIcon(QIcon(":/Ressource/image/pawn.png"));
	}



}


void JeuEchecWindow::eliminationPieceVue(const QIcon& icon, bool estImageNoir) {
	int rangee= 8;
	int colonne = 2;


	bool listeBlancheVide = plateau->listeTeamBleu.empty();
	bool listeNoireVide = plateau->listeTeamRouge.empty();

	if ((listeBlancheVide == false && estImageNoir == false) || (listeNoireVide == false && estImageNoir == true)) {


		for (int i = 0; i < rangee; i++) {
			for (int j = 0; j < colonne; j++) {

				
				bool caseVideListeNoire = (ui->listeNoire->item(i, j))->icon().isNull();
				bool caseVideListeBlanche = ui->listeBlanche->item(i, j)->icon().isNull();

				if (estImageNoir && caseVideListeNoire) {

	
					ui->listeNoire->item(i, j)->setIcon(icon);

					return;

				}
				else if (estImageNoir == false && caseVideListeBlanche) {

			
					ui->listeBlanche->item(i, j)->setIcon(icon);

					return;

				}
			}
		}
	}
}


void JeuEchecWindow::messageMouvementInvalide(shared_ptr<Piece> pieceSelectionneModele, Position positionFinale,bool echec) {

	QString message = QString::fromStdString(plateau->mouvementInterditMessage(pieceSelectionneModele, { positionFinale.x,positionFinale.y + 1 }));
	QString messageLong = "<FONT COLOR='#ffffff'>" + message + "." + "\n" + "</FONT>";

	if ((pieceSelectionneModele->pareilCouleur(plateau->getPiece(positionFinale.x, positionFinale.y + 1)))) {

		messageLong += "<FONT COLOR='#ffffff'>  : Vous ne pouvez pas bouffer vos propres pieces! </FONT> ";
	}
	if (echec) {
		messageLong += "Votre roi est en echec";
	}

	QMessageBox::warning(this, "Mouvement interdit", messageLong);


}


void JeuEchecWindow::effetMusiqueDeplacement(){
	if (musiqueDeplacement->state() == QMediaPlayer::PlayingState) {
		musiqueDeplacement->setPosition(0);
	}
	else if (musiqueDeplacement->state() == QMediaPlayer::StoppedState) {
		musiqueDeplacement->play();
	}

}


void JeuEchecWindow::mouvementValide(shared_ptr<Piece> pieceAttaquanteModel, Position positionFinale) {

	shared_ptr<Piece> pieceAttaquee = plateau->getPiece(positionFinale.x, positionFinale.y + 1);


	bool caseDestinationVide = (ui->tableWidget->item(positionFinale.x, positionFinale.y)->icon().isNull());

	plateau->deplacementPiece(pieceAttaquanteModel, { positionFinale.x,positionFinale.y + 1 },false);
	

	if (caseDestinationVide == false) {

		eliminationPiece(pieceAttaquanteModel);

	}



	
	auto pieceAttaquanteVue = ui->tableWidget->item(positionPieceSelectionne.x, positionPieceSelectionne.y);

	ui->tableWidget->item(positionFinale.x, positionFinale.y)->setIcon(pieceAttaquanteVue->icon());
	pieceAttaquanteVue->setIcon(QIcon());



}

void JeuEchecWindow::eliminationPiece(shared_ptr<Piece> pieceAttaquee) {

	
	

	int positionPieceX = pieceAttaquee->getPositionActuelle().x;
	int positionPieceY = pieceAttaquee->getPositionActuelle().y-1;

	bool estNoir = !(pieceAttaquee->getCouleur() == Couleur::noir);
	auto imagePiece = ui->tableWidget->item(positionPieceX, positionPieceY)->icon();


	eliminationPieceVue(imagePiece, estNoir);


}
void JeuEchecWindow::deplacementPiece(int positionFinaleX, int positionFinaleY) {

	//Premier clic : Selection piece
	bool caseVide = ui->tableWidget->item(positionFinaleX, positionFinaleY)->icon().isNull();
	if (premierClic && caseVide == false) {

		auto couleur = plateau->getPiece(positionFinaleX, positionFinaleY + 1)->getCouleur();

		if (tourBlanc && couleur == Couleur::blanc || !tourBlanc && couleur == Couleur::noir) {
			positionPieceSelectionne.x = positionFinaleX;
			positionPieceSelectionne.y = positionFinaleY;
			premierClic = false;
			coloriageCaseValide({ positionFinaleX,positionFinaleY });
		}


	}

	//Deuxieme clic : Deplacement piece

	else if (premierClic == false) {
		
		remettreCouleurCaseAvant();
		listeCaseColoriee.clear();

		shared_ptr<Piece> pieceSelectionnee = plateau->getPiece((positionPieceSelectionne.x), positionPieceSelectionne.y + 1);
		if (pieceSelectionnee->getPositionActuelle().positionNumerotation() == "d8") {
			cout << "a";
		}

		bool caseDifferente = (positionPieceSelectionne.x != positionFinaleX || positionPieceSelectionne.y != positionFinaleY);
		bool deplacementValide = plateau->mouvementValide(pieceSelectionnee, { positionFinaleX,positionFinaleY + 1 });
		bool echec = plateau->deplacementEchec(pieceSelectionnee, { positionFinaleX,positionFinaleY + 1 });

		if (caseDifferente){

			if (deplacementValide && echec == false) {

				mouvementValide(pieceSelectionnee, { positionFinaleX,positionFinaleY });
				effetMusiqueDeplacement();

				tourBlanc = !tourBlanc;

				if (tourBlanc == false)
					ui->tourRole->setText("Tour : NOIR");
				else {
					ui->tourRole->setText("Tour : BLANC");
				}

			}

			else {

					messageMouvementInvalide(pieceSelectionnee, { positionFinaleX,positionFinaleY },echec);	

			}
	}


		premierClic = true;


	}


}

JeuEchecWindow::~JeuEchecWindow()
{

	delete ui;
	delete musiqueDeplacement;
}