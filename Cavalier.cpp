#include <iostream>
#include <string>
#include "Cavalier.h"
#include "Ajout.h"
#include <cmath>
#include "Piece.h"


std::shared_ptr<Piece> Cavalier::Cavalier::getInstanceCavalierGauche(Couleur couleur) {
    
   
    if (cavalier1 == nullptr && couleur == Couleur::blanc) {

        cavalier1 = make_shared<Cavalier>(Cavalier({ 0,7 }, Couleur::blanc, "Cavalier blanc G"));

        return cavalier1;
    }
    else if(cavalier1 != nullptr && couleur == Couleur::blanc) {

        return cavalier1;
    }

    if (cavalier2 == nullptr && couleur == Couleur::noir) {

        cavalier2 = make_shared<Cavalier>(Cavalier({ 7,2 }, Couleur::noir, "Cavalier noir G"));

        return cavalier2;
    }
    else if (cavalier2 != nullptr && couleur == Couleur::noir) {

        return cavalier2;
    }

}

std::shared_ptr<Piece> Cavalier::Cavalier::getInstanceCavalierDroite(Couleur couleur) {

    if (cavalier3 == nullptr && couleur == Couleur::blanc) {

        cavalier3 = make_shared<Cavalier>(Cavalier({ 0,2 }, Couleur::blanc, "Cavalier blanc D"));

        return cavalier3;
    }
    else if(cavalier3 != nullptr && couleur == Couleur::blanc) {

        return cavalier3;
    }

    if (cavalier4 == nullptr && couleur == Couleur::noir) {

        cavalier4 = make_shared<Cavalier>(Cavalier({ 7,7 }, Couleur::noir, "Cavalier noir D"));

        return cavalier4;
    }
    else if (cavalier4 != nullptr && couleur == Couleur::noir) {

        return cavalier4;
    }

}



Cavalier::Cavalier::Cavalier(Position position, Couleur couleur, string nom) : Piece(position, couleur, nom) {

    cout << "La piece " << this->nom_ << " a ete cree a l'endroit ";
    position.positionNumerotation();
    cout << "\n";

}


bool Cavalier::Cavalier::validationMouvement(Position positionApres, vector<vector<shared_ptr<Piece>>>& tableauEchec) {


    if (((abs(positionApres.x - positionActuelle.x) == 1)) && (abs(positionApres.y - positionActuelle.y)) == 2) {

        return true;
    }
    else if (((abs(positionApres.x - positionActuelle.x) == 2)) && (abs(positionApres.y - positionActuelle.y)) == 1) {

        return true;
    }

    return false;

}
