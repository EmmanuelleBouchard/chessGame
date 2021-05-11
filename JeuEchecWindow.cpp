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
	connect(ui->listeNoire, SIGNAL(cellClicked(int, int)), this, SLOT(promotionNoir(int, int)));
	connect(ui->listeBlanche, SIGNAL(cellClicked(int, int)), this, SLOT(promotionBlanc(int, int)));



	initialisationFenetre();


}

void JeuEchecWindow::promotionNoir(int x, int y) {

	promotion(x, y,false);

}
void JeuEchecWindow::promotionBlanc(int x, int y) {

	promotion(x, y,true);

}

void JeuEchecWindow::promotion(int x, int y, bool listeChoisiBlanche) {
	if (plateau->promotion) {
		auto pionModele = plateau->getPiece(positionPieceSelectionne.x, positionPieceSelectionne.y + 1);
		auto imagePion = ui->tableWidget->item(positionPieceSelectionne.x, positionPieceSelectionne.y)->icon();
		bool estPionNoir = pionModele->getCouleur() == Couleur::noir;


		auto pieceVuePromotion = (estPionNoir) ? ui->listeNoire->item(x, y) : ui->listeBlanche->item(x, y);
		bool caseVideListe = pieceVuePromotion->icon().isNull();

		bool verificationListe = (estPionNoir == false and listeChoisiBlanche == true) or (estPionNoir == true and listeChoisiBlanche == false);
		if (caseVideListe == false and verificationListe) {

			plateau->promotionPion(x, y, pionModele);
		
			ui->tableWidget->item(positionPieceSelectionne.x, positionPieceSelectionne.y)->setIcon(pieceVuePromotion->icon());
			auto indexPionDeplace = pionModele->getPositionActuelle();

			if (estPionNoir == false) {


				ui->listeBlanche->item(indexPionDeplace.x, indexPionDeplace.y)->setIcon(imagePion);
				QString messageNoir = QString("Tour : <font color =#8696FF > Noir < / font>");
				ui->tourRole->setText(messageNoir);
		
			}
			else if(estPionNoir == true){
				ui->listeNoire->item(indexPionDeplace.x, indexPionDeplace.y)->setIcon(imagePion);
				QString messageBlanc = QString("Tour : <font color = #FF7676> Blanc < / font>");
				ui->tourRole->setText(messageBlanc);

			}

			pieceVuePromotion->setIcon(QIcon());
			plateau->promotion = false;

		}
	

	}

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

	QString message = QString("Tour : <font color = #FF7676 > Blanc < / font>");
	
	ui->tourRole->setText(message);
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





void JeuEchecWindow::messageMouvementInvalide(shared_ptr<Piece> pieceSelectionneModele, Position positionFinale,bool echec) {

	QString message = QString::fromStdString(plateau->mouvementInterditMessage(pieceSelectionneModele, { positionFinale.x,positionFinale.y + 1 }));
	QString messageLong = "<FONT COLOR='#ffffff'>" + message + "." + "\n" + "</FONT>";

	if ((pieceSelectionneModele->pareilCouleur(plateau->getPiece(positionFinale.x, positionFinale.y + 1)))) {

		messageLong += "<FONT COLOR='#ffffff'>  : Vous ne pouvez pas bouffer vos propres pieces! </FONT> ";
	}
	if (echec) {
		messageLong += "Votre roi est en echec";
	}

	//QMessageBox::warning(this, "Mouvement interdit", messageLong);


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

		eliminationPieceVue(pieceAttaquanteModel, pieceAttaquee);

	}



	
	auto pieceAttaquanteVue = ui->tableWidget->item(positionPieceSelectionne.x, positionPieceSelectionne.y);

	ui->tableWidget->item(positionFinale.x, positionFinale.y)->setIcon(pieceAttaquanteVue->icon());
	pieceAttaquanteVue->setIcon(QIcon());



}

void JeuEchecWindow::eliminationPieceVue(shared_ptr<Piece> pieceAttaquante, shared_ptr<Piece> pieceAttaquee) {

	
	

	int positionPieceX = pieceAttaquante->getPositionActuelle().x;
	int positionPieceY = pieceAttaquante->getPositionActuelle().y-1;

	bool estImageNoir = !(pieceAttaquante->getCouleur() == Couleur::noir);
	auto imagePiece = ui->tableWidget->item(positionPieceX, positionPieceY)->icon();



	bool listeBlancheVide = plateau->listeTeamBleu.empty();
	bool listeNoireVide = plateau->listeTeamRouge.empty();

	if ((listeBlancheVide == false && estImageNoir == false) || (listeNoireVide == false && estImageNoir == true)) {
		auto indexPieceEliminee = pieceAttaquee->getPositionActuelle();
		bool caseVideListeNoire = (ui->listeNoire->item(indexPieceEliminee.x, indexPieceEliminee.y))->icon().isNull();
		bool caseVideListeBlanche = ui->listeBlanche->item(indexPieceEliminee.x, indexPieceEliminee.y)->icon().isNull();

		if (estImageNoir && caseVideListeNoire) {


			ui->listeNoire->item(indexPieceEliminee.x, indexPieceEliminee.y)->setIcon(imagePiece);

			return;

		}
		else if (estImageNoir == false && caseVideListeBlanche) {


			ui->listeBlanche->item(indexPieceEliminee.x, indexPieceEliminee.y)->setIcon(imagePiece);

			return;

		}


	}


}
void JeuEchecWindow::deplacementPiece(int positionFinaleX, int positionFinaleY) {
	if (plateau->promotion == false) {
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
			plateau->promotion = false;

		}

		//Deuxieme clic : Deplacement piece

		else if (premierClic == false) {

			remettreCouleurCaseAvant();
			listeCaseColoriee.clear();

			shared_ptr<Piece> pieceSelectionnee = plateau->getPiece((positionPieceSelectionne.x), positionPieceSelectionne.y + 1);
			

			bool caseDifferente = (positionPieceSelectionne.x != positionFinaleX || positionPieceSelectionne.y != positionFinaleY);
			bool deplacementValide = plateau->mouvementValide(pieceSelectionnee, { positionFinaleX,positionFinaleY + 1 });
			bool echec = plateau->deplacementEchec(pieceSelectionnee, { positionFinaleX,positionFinaleY + 1 });

			if (caseDifferente) {

				if (deplacementValide && echec == false) {

					mouvementValide(pieceSelectionnee, { positionFinaleX,positionFinaleY });
					effetMusiqueDeplacement();
					//Revive modele et vue
					positionPieceSelectionne.x = positionFinaleX;
					positionPieceSelectionne.y = positionFinaleY;

					tourBlanc = !tourBlanc;
					QString messageNoir = QString("Tour : <font color =#8696FF > Noir < / font>");
					QString messageBlanc = QString("Tour : <font color = #FF7676> Blanc < / font>");
					

					if (plateau->promotion) {
						QString message = QString("Veuillez choisir une piece a echanger avant de continuer");
						ui->tourRole->setText(message);

					}else{
					if (tourBlanc == false)
						ui->tourRole->setText(messageNoir);
					else {
						ui->tourRole->setText(messageBlanc);
					}
				}

				}

				else {

					messageMouvementInvalide(pieceSelectionnee, { positionFinaleX,positionFinaleY }, echec);

				}
			}


			premierClic = true;


		}


	}
}
JeuEchecWindow::~JeuEchecWindow()
{

	delete ui;
	delete musiqueDeplacement;
}