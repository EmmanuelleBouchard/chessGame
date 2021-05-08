
#include "JeuEchecWindow.h"

#include <QApplication>
#include <iostream>
#include <vector>
#include "Ajout.h"
#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Tour.h"
#include "Pion.h"
#include "FenetreDemarrage.h"
#include "PlateauEchec.h"
#include <QDesktopWidget>
#include <qguiapplication.h>

int main(int argc, char *argv[])
{

	

	QApplication a(argc, argv);

	QSharedPointer<JeuEchecWindow> p(new JeuEchecWindow());
	QSharedPointer<FenetreDemarrage> w(new FenetreDemarrage());
	

	QObject::connect(w.get(), &FenetreDemarrage::clicked, p.get(), &JeuEchecWindow::MakeActive);
	QObject::connect(w.get(), &FenetreDemarrage::liste1, p.get(), &JeuEchecWindow::liste1);
	QObject::connect(w.get(), &FenetreDemarrage::liste2, p.get(), &JeuEchecWindow::liste2);

	QObject::connect(w.get(), &FenetreDemarrage::liste1, p.get(), &JeuEchecWindow::MakeActive);
	QObject::connect(w.get(), &FenetreDemarrage::liste2, p.get(), &JeuEchecWindow::MakeActive);

	w->show();

	return a.exec();
	
	
	
}
