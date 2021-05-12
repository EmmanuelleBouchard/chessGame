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




public slots:
    void signalClicked();
    void MakeActive();


  

private:
    Ui::FenetreDemarrage *ui_;
  
 
};
#endif // FENETREDEMARRAGE_H
