#ifndef FENETREDEMARRAGE_H
#define FENETREDEMARRAGE_H
#include "PlateauEchec.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FenetreDemarrage; }
QT_END_NAMESPACE

class FenetreDemarrage : public QMainWindow
{
    Q_OBJECT

public:
    FenetreDemarrage(QWidget *parent = nullptr);
  
    ~FenetreDemarrage();

signals:
    void clicked();
    void liste1();
    void liste2();



public slots:
    void signalClicked();
    void signalListe1();
    void signalListe2();


  

private:
    Ui::FenetreDemarrage *ui_;
  
 
};
#endif // FENETREDEMARRAGE_H
