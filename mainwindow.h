#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QPainter>
#include <QRectF>
#include "pierre.h"
#include <QMouseEvent>
#include <QVector>
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>
#include <QSoundEffect>
#include "dialogtheme.h"
#include "dialogoption.h"
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
     QVector <pierre*> vPierre; // conntient les pierres
     QVector <QPoint> vPoint; // contient les points
     QPoint pointDepart; // le point de départ de la pierre déplacée
     QVector <int> ouAller(int point); // renvoi les points ou on peut aller
     QVector <int> vAutorizedPoints; // contient les points ou aller
     QVector <int> vAutorizedPointsOrdi; // contient les points ou aller
     QVector <int> OuallerOrditemp; // contient les points ou aller

     void cout(QVariant);
     void mouseMoveEvent(QMouseEvent *ev);
     void mouseReleaseEvent(QMouseEvent *ev);
     void defPoints(); // definie les points
     void movePierreSiPOssible(QMouseEvent); // gere le déplacement
     void creerPierre(); // crée les pierres
     void initialisation();
     void gererTOur(); // change de joueur
     void GetVectorOuAller();
     void isBlocked(); //true su un pierre est bloquée
     void checkIfWinner();// verifie si qqn a gagné
     void creerTxtVictoire(); // crée le texte de la victoire
     void creerSon(); // créée les sons
     void gererTheme(int); // change le theme
     void movePierreSiPOssible(QPoint epos);
     void pierreBackground(bool);
     void afficheOption();
     void gererOrdinateur();
     void gerePlacementOrdi();
     void goWinOrdiIfPOssible();
     void gereJeuOrdi();

    //true si :
     bool surLePlateau(); // toutes les pierres sont jouées
     bool onDeplace;  // si on peut déplacer
     bool blocked; // si la pierre est bloquée
     bool diagoJ1(); //true si le J1  a fait une diagonale
     bool diagoJ2();//true si le J2  a fait une diagonale
     bool doEvent; // si on a cliqué su une pierre
     bool ordiJoue;
     bool placeLibre(int);
     bool checkIfJ1WillWon();// pour la pose de la 2eme pierre
     bool checkIfJ1WillWon2();// pour la pose de la 3eme pierre
     bool checkIfJ1WillWonJeu();// pour la pose de la 3eme pierre
     bool diagoJ1Ordi(int n1,int n2,int n3);// pour la pose de la 2eme pierre
     bool goWinOrdiIfPOssibleJeu();
     bool GoRandomPLaceJeu();


     int currentPierre;//la pierre qui est cliquée
     int quiJoue; // 1 = J1 2 = J2
     int getNoPoint(QPoint);  // renvoi le numero du point le + proche passé en parametres
     int getNoByPoint(QPoint p); // renvoi les numero de Qpoint passé en parametre
     int gereDeplacement; // si il n est pas =1 quand on move , on movera pas
     int currentTheme;// le theme actuel
     int plateauHauteur;
     int nbAletat(int nbMax, int nbMin, int valeurInterdite);
     int noPierreADeplacer_Ordi;

     QPoint getPOintByNo(int no);
     QPoint fautYAllerOrdi;
    QLabel * w; // label de victoire
    QLabel * w2;// label de victoire
    QLabel * w3;// label de victoire
    QPixmap getIconePLayer(); // renvoi l'incone de joueur en fonction du currentTheme
    QSoundEffect * fond; // differents sound
    QSoundEffect * dommage;
    QSoundEffect * reussi;
    QSoundEffect * victoire;
    QMovie * movieMario;


public slots:
     void on_pushButtonNewGame_clicked(); // nouvelle partie

     void on_pushButtonQuitter_clicked(); // on quitte

     void on_pushButtonThemes_clicked(); //on change de theme

     void on_pushButtonNewGameHaut_clicked(); // nouvelle partie



     void on_pushButtonOptions_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H



