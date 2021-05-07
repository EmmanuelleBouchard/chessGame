
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

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
using bibliotheque_cours::cdbg;
#else
auto& cdbg = clog;
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette ent�te si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#endif



void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par d�faut.

	// cdbg.setTee(&clog);  // D�commenter cette ligne pour que cdbg affiche sur la console en plus de la "Sortie" du d�bogueur.

	bibliotheque_cours::executerGoogleTest(argc, argv); // Attention de ne rien afficher avant cette ligne, sinon l'Explorateur de tests va tenter de lire votre affichage comme un r�sultat de test.
#endif
//NOTE: C'est normal que la couverture de code dans l'Explorateur de tests de Visual Studio ne couvre pas la fin de cette fonction ni la fin du main apr�s l'appel � cette fonction puisqu'il ex�cute uniquement les tests Google Test dans l'appel ci-dessus.
}

int main(int argc, char *argv[])
{

	

	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;

	initialiserBibliothequeCours(argc, argv);

	

	
	/*
	QApplication a(argc, argv);
	JeuEchecWindow w;
	w.show();
	return a.exec();
	*/
	
	
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
