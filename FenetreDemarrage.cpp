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

   
    
}
void FenetreDemarrage::signalClicked(){

    this->close();
    emit clicked();
}


FenetreDemarrage::~FenetreDemarrage()
{

    delete ui_;

}


void FenetreDemarrage::MakeActive() {
    raise();
    this->show();
    this->activateWindow();
    this->raise();
}



