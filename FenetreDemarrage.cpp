#include "FenetreDemarrage.h"
#include "ui_FenetreDemarrage.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Fou.h"
#include "Ajout.h"
#include "PlateauEchec.h"


FenetreDemarrage::FenetreDemarrage(QWidget* parent)
    : QMainWindow(parent)
    , ui_(new Ui::FenetreDemarrage)
{
    ui_->setupUi(this);
    connect(ui_->start, SIGNAL(pressed()), this, SLOT(signalClicked()));
    connect(ui_->liste1, SIGNAL(pressed()), this, SLOT(signalListe1()));
    connect(ui_->liste2, SIGNAL(pressed()), this, SLOT(signalListe2()));
    

    
   
    
}
void FenetreDemarrage::signalClicked(){
    this->hide();
    emit clicked();
}
void FenetreDemarrage::signalListe1() {
    this->hide();

    emit liste1();

}
void FenetreDemarrage::signalListe2() {
    this->hide();
    emit liste2();

}

FenetreDemarrage::~FenetreDemarrage()
{


    delete ui_;

}




