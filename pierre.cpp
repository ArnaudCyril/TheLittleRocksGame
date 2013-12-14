#include "pierre.h"
#include <QPixmap>
#include <QDebug>
#include "mainwindow.h"
pierre::pierre(QWidget *parent,int i) :
    QLabel(parent)
{



    noPierre=i;
    if(i>3) // si c est la 4eme , 5eme ou 6eme pierre (J2)
    {
        setGeometry(-20+(i%4+1)*120,655,83,83); // on défini le placement de la pierre en fonction de son numéro
        setPixmap(QPixmap(":/Images/golf2.png").scaled(83,83));
    }
    else //si c est le J1
    {
        setGeometry(-80+i*120,590,83,83); // on défini le placement de la pierre en fonction de son numéro
        setPixmap(QPixmap(":/Images/golf1.png").scaled(83,83));
    }
    setStyleSheet("background-color:rgba(0,0,0,0)");

}

void pierre::mousePressEvent(QMouseEvent *ev) // si on press une pierre
{
    if( ((MainWindow *)parent())->gereDeplacement==0) // si aucune pierre n'est déja sélectionné
    {

      ((MainWindow *)parent())->currentPierre=noPierre; // on définie la currentPierre en fonction du numéro de la pierre cliquée
    ((MainWindow *)parent())->doEvent=true; // on a cliqué sur une pierre => on peut bouger

    if(this->y()<=((MainWindow * )parent())->plateauHauteur) // si la pierre a deja été jouée
    {
        ((MainWindow *)parent())->pointDepart=this->pos();
    }
    else
    {

    if(noPierre<4)((MainWindow *)parent())->pointDepart=QPoint(-80+noPierre*120,580);
    else ((MainWindow *)parent())->pointDepart=QPoint((noPierre%4+1)*120,665);//sinon on remet la pierre sur sa place initiale


    }
     ((MainWindow *)parent())->GetVectorOuAller(); // on definie les destinations possibles
    ((MainWindow *)parent())->isBlocked(); // on regarde si il est bloqué
     ((MainWindow *)parent())->gereDeplacement++; // gere les doublons de déplacement
    }




}
bool pierre::surLePLateau() // renvoie true si la pierre est sur le plateau
{
    return(this->y()<((MainWindow * )parent())->plateauHauteur);
}






