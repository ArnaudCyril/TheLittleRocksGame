#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"
#include <QDebug>
#include <QPainter>
#include <QRectF>
#include "pierre.h"
#include <QMovie>
#include <QLabel>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QMediaContent>
#include <QMessageBox>
#include "dialogtheme.h"
#include <QPixmap>
#include <QAudioOutput>
#include <QStatusBar>
#include <QAudioDeviceInfo>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cout("pll");

    ui->setupUi(this);
    creerPierre(); //creation des "pierres" (classe cpp)
     defPoints(); // on cree les points sur le plateau
     creerTxtVictoire();// initialisation du texte a afficher en cas de victoire
     creerSon(); // creation des sons
    initialisation(); // initialisation des diverses variable utiles au jeu
    gererTheme(1);// definition du theme 1


}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::cout(QVariant var) // methode cout , plus rapide que qDebug()<<....
{
    qDebug()<<var;
}
void MainWindow::mouseMoveEvent(QMouseEvent *ev) // quand la souris bouge
{

    if(doEvent and gereDeplacement==1) // si on a cliqué sur une pierre et qu'aucune pierre n'est deja en deplacement
    {
         onDeplace=false; // on a pas déplacé
         vPierre.value(currentPierre-1)->raise();

        if(surLePlateau()==false and pointDepart.y()>plateauHauteur) // si il reste des pierres a jouer au début et que la pierre choisie n'est pas deja sur le plateau
        {

          if(quiJoue==1 and currentPierre<4 or (quiJoue==2 and currentPierre>3))// si c est au J1 et que la pierre cliqué est au J1 (ou onversement pour J2)
          {


                onDeplace=true;// on va déplacer
                vPierre.value(currentPierre-1)->move(ev->pos()-QPoint(vPierre.value(0)->width()/2,vPierre.value(0)->height()/2));//on déplace
           }
          else// sinon
          {
            gereDeplacement=0; // on bouge pas est on remet la variable a 0. Cette variable permet de gerer le déplacement : elle est a 0 , puis a 1 quand on clique donc si on clique sur 2 pierre en meme temps , la variable sera a 2 et on  ne permet pas le déplacement
          }

       }
       if(surLePlateau()) // si tout les pions sont posés
       {
            if((quiJoue==1 and currentPierre<4 or (quiJoue==2 and currentPierre>3)) and blocked==false and pointDepart.y()<plateauHauteur) // voir plus haut + si la pierre n'est pas bloquée
            {
              onDeplace=true;// on bouge la pierre
              vPierre.value(currentPierre-1)->move(ev->pos()-QPoint(vPierre.value(0)->width()/2,vPierre.value(0)->height()/2));
            }
            else
            {
              gereDeplacement=0;// voir + haut
            }

       }
        if(onDeplace==false)
        {
            dommage->play();
            gereDeplacement=0;
        }// si on a pas déplacé on remet cette variable a 0
    }


}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)// quand on lache la pierre
{
    if(doEvent and onDeplace) //si on a pu la déplacer
    {
    gereDeplacement=0; // on peut reselectionner une pierre

     movePierreSiPOssible(ev->pos()); // on met la pierre la ou il faut si possible

     if(quiJoue==1) // on change l'affichage du tour des joueurssi c est qu joueur 1 de jouer
     {
         ui->label_2->setText("    Joueur 1    ");
         ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
         ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
     }
     else // si c est au joueur 2
     {
         ui->label_2->setText("    Joueur 2    ");
         ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
         ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
     }
      checkIfWinner(); // on a déposé une pierre , on verifie si qqn a gagné
      doEvent=false; //on reinitialise l'autorisation de bouger
    }
    if(ordiJoue and quiJoue==2)
    {
        gererOrdinateur();
    }

}

void MainWindow::movePierreSiPOssible(QPoint epos) // on bouge la pierre sur le point si c est possible
{
   int x=epos.x()-vPierre.value(0)->width()/2,y=epos.y()-vPierre.value(0)->height()/2; // on definie la position de l evenement pour simplifier las calculs
   int diff=10000;// on initialisa la difference a un nombre tres grand
   int noPoint; // declaration des variables
   int diffTempX,diffTempY;
   for(int i=0;i<vPoint.size();i++) // pour chaque point
   {

       diffTempX=x-vPoint.value(i).x(); // on calcule la difference des x entre la position vPoint().value   et la position de l evenement
       diffTempY=y-vPoint.value(i).y(); // on calcule la difference des y entre la position vPoint().value   et la position de l evenement
       if(diffTempX<0)diffTempX=diffTempX*(-1); // si la difference est negative , on l inverse
       if(diffTempY<0)diffTempY=diffTempY*(-1); // si la difference est negative , on l inverse

       if(diffTempX+diffTempY<diff) // si la difference totale est + petite que le point précedent
        {
            noPoint=i; // on recupere le numéro du point
            diff=diffTempX+diffTempY; // on actualise la valeur diff
       }


   }

    bool OnYVas=false; // on regarde si le point est a coté
    for(int i=0;i<vAutorizedPoints.size();i++)
    {

        if(vAutorizedPoints.value(i)==noPoint+1)
         {
            OnYVas=true; // si le point ou il veut aller est accessible , onYvas
        }
    }
    if(pointDepart.y()>plateauHauteur)OnYVas=true; // si le pion n'est pas encore déplacé on peut le bouger , il peut aller sur toute les cases

   if(vPierre.value(0)->pos()!=vPoint.value(noPoint) and vPierre.value(1)->pos()!=vPoint.value(noPoint) and vPierre.value(2)->pos()!=vPoint.value(noPoint) and vPierre.value(3)->pos()!=vPoint.value(noPoint) and vPierre.value(4)->pos()!=vPoint.value(noPoint) and vPierre.value(5)->pos()!=vPoint.value(noPoint) and diff<60 and OnYVas) // si le point n'est pas occupé , qu'on est assez proche et que le point est autorisé
   {
             reussi->play();// on joue la musique
             gererTOur(); // on change les tours
             vPierre.value(currentPierre-1)->move(vPoint.value(noPoint));// on bouge le point
   }
   else
   {

             dommage->play();// on joue la musique d'echec
             vPierre.value(currentPierre-1)->move(pointDepart);// on redéplace la pierre a son point de départ si le déplacement n'est pas bon

   }

}

void MainWindow::pierreBackground(bool var)
{
    if(var)
    {
        for(int i=0;i<vPierre.size();i++)
        {
           vPierre.value(i)->lower();
        }
    }
    else
    {
        for(int i=0;i<vPierre.size();i++)
        {
           vPierre.value(i)->raise();
        }
    }
}


void MainWindow::creerPierre() // méthode qui crée la pierre , en passant en parametre le numéro de la pierre
{
    for(int i=0;i<6;i++) // on, crée 6 pierre
    {
        vPierre.push_back(new pierre(this,i+1));
    }

}

void MainWindow::gererTOur() // methode qui inverse les tours quand un joueur a joué
{
    if(currentPierre<4 and quiJoue==1 and pointDepart!=vPierre.value(currentPierre-1)->pos())
    {

        quiJoue=2;
    }

      if(currentPierre>3 and quiJoue==2 and pointDepart!=vPierre.value(currentPierre-1)->pos())
     {
        quiJoue=1;
    }



}
int MainWindow::getNoPoint(QPoint poit)//méthode qui renvoi le numéro du point le plus proche en fonction du QPoint passé en parametres
{

    int x=pointDepart.x(),y=pointDepart.y(); //on a déja vu ca quelque part... (moveIfPossible)
    int diff=10000;
    int noPoint;
    int diffTempX,diffTempY;
    for(int i=0;i<vPoint.size();i++)
    {

        diffTempX=x-vPoint.value(i).x();
        diffTempY=y-vPoint.value(i).y();
        if(diffTempX<0)diffTempX=diffTempX*(-1);
        if(diffTempY<0)diffTempY=diffTempY*(-1);
        if(diffTempX+diffTempY<diff)
         {
             noPoint=i;
             diff=diffTempX+diffTempY;
        }


    }

    return noPoint+1;
}



bool MainWindow::surLePlateau() //métode qui renvoie true si toutes les pierres ont été jouées , false sinon
{

    for(int i=0;i<vPierre.size();i++)
    {

        if(pointDepart.y()>=plateauHauteur)
        {
            return false;
        }
        if(vPierre.value(i)!=vPierre.value(currentPierre-1) and vPierre.value(i)->surLePLateau()==false)
        {
            return false;

        }

    }
    return true;
}

QVector <int> MainWindow::ouAller(int point) // méthode qui renvoi un vecteur composé des numéros de point ou le joueur peut aller en fonction du numéro de point ou il se trouve
{
    QVector <int> vPoint;
    switch (point) {
    case 1:vPoint.push_back(2);vPoint.push_back(4);vPoint.push_back(5); break; // si il est sur la case 1 , il peut aller au point 2,4,5
    case 2:vPoint.push_back(1);vPoint.push_back(3);vPoint.push_back(5); break;
    case 3:vPoint.push_back(2);vPoint.push_back(6);vPoint.push_back(5); break;
    case 4:vPoint.push_back(1);vPoint.push_back(7);vPoint.push_back(5); break;

    case 5:vPoint.push_back(1);vPoint.push_back(2);vPoint.push_back(3);vPoint.push_back(4);vPoint.push_back(6);vPoint.push_back(7);vPoint.push_back(8);vPoint.push_back(9); break;

    case 6:vPoint.push_back(3);vPoint.push_back(9);vPoint.push_back(5); break;
    case 7:vPoint.push_back(4);vPoint.push_back(8);vPoint.push_back(5); break;
    case 8:vPoint.push_back(7);vPoint.push_back(9);vPoint.push_back(5); break;
    case 9:vPoint.push_back(6);vPoint.push_back(8);vPoint.push_back(5); break;



    }
    return vPoint;
}
int MainWindow::getNoByPoint(QPoint p)//méthode qui renvoie le QPoint le plus proche en fonction du point passé
{
    for(int i=0;i<vPoint.size();i++)
    {
        if(p==vPoint.value(i))
        {
            return i+1;
        }
    }
    return -1;
}




void MainWindow::isBlocked()//méthode qui renvoie true si la pierre est bloquée , false sinon
{
    int nbTest=0;
    for(int i=0;i<vAutorizedPoints.size();i++) // pour tout les points autorisés
    {

        if(getNoByPoint(vPierre.value(0)->pos())==vAutorizedPoints.value(i) or  getNoByPoint(vPierre.value(1)->pos())==vAutorizedPoints.value(i) or  getNoByPoint(vPierre.value(2)->pos())==vAutorizedPoints.value(i) or  getNoByPoint(vPierre.value(3)->pos())==vAutorizedPoints.value(i) or  getNoByPoint(vPierre.value(4)->pos())==vAutorizedPoints.value(i) or  getNoByPoint(vPierre.value(5)->pos())==vAutorizedPoints.value(i))//si il y a une pierre a l emplacement vAuthorizedPoint.value(i)
            {
             nbTest++;
            }
    }

    if(nbTest>=3 and getNoByPoint(vPierre.value(currentPierre-1)->pos())!=5)blocked=true; // si il y a 3 pierre autour et que la pierre qu'on veut déplacer n'est pas sur la case 5 , on est bloqué
    else blocked=false; // sinon on est pas bloqué
}

void MainWindow::checkIfWinner()// methode qui verifie si un joueur a gagné
{
    if(vPierre.value(0)->surLePLateau() and vPierre.value(1)->surLePLateau() and vPierre.value(2)->surLePLateau())// si le J1 a joué toutes ses pierres
    {
        bool ligneJ1=vPierre.value(0)->x()==vPierre.value(1)->x() and vPierre.value(0)->x()==vPierre.value(2)->x() and vPierre.value(2)->x()==vPierre.value(1)->x(); //si toutes les pierres du J1 on le meme x , c'est qu'il a fait une ligne
        bool colonneJ1=vPierre.value(0)->y()==vPierre.value(1)->y() and vPierre.value(0)->y()==vPierre.value(2)->y() and vPierre.value(2)->y()==vPierre.value(1)->y();//si toutes les pierres du J1 on le meme y , c'est qu'il a fait une colonne
        bool ligneJ2=vPierre.value(3)->x()==vPierre.value(4)->x() and vPierre.value(3)->x()==vPierre.value(5)->x() and vPierre.value(5)->x()==vPierre.value(4)->x();//si toutes les pierres du J2 on le meme x , c'est qu'il a fait une ligne
        bool colonneJ2=vPierre.value(3)->y()==vPierre.value(4)->y() and vPierre.value(3)->y()==vPierre.value(5)->y() and vPierre.value(5)->y()==vPierre.value(4)->y();//si toutes les pierres du J2 on le meme y , c'est qu'il a fait une colonne


    if(ligneJ1 or colonneJ1 or diagoJ1())//si le J1 a fait une ligne , une diagonale ou un colonne , il a gagné
    {
        w->setVisible(true);
        w2->setVisible(true);
        w3->setVisible(true); // on affiche qui le joueur a gagné avec des gifs et tout !
        w3->setText(" Victoire du Joueur 1");

        quiJoue=1; // pas utile mais + sympa a l affichage
        ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40)); //de même
        vPierre.value(0)->setEnabled(false);
        vPierre.value(1)->setEnabled(false);
        vPierre.value(2)->setEnabled(false); // on enabled false les pierres
        if(vPierre.value(3)->surLePLateau()==false)vPierre.value(3)->setHidden(true);
        vPierre.value(3)->setEnabled(false);
        if(vPierre.value(4)->surLePLateau()==false)vPierre.value(4)->setHidden(true);
        vPierre.value(4)->setEnabled(false);
        if(vPierre.value(5)->surLePLateau()==false)vPierre.value(5)->setHidden(true);
        vPierre.value(5)->setEnabled(false);
        ui->pushButtonNewGame->setVisible(true); // on affiche les option de fin de jeu
        ui->pushButtonQuitter->setVisible(true);
      victoire->play(); // on joue le son de la victoire
       ui->label_2->setText("  Joueur 1  "); // pas obligatoire mais + sympa
       ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
       w->raise();w2->raise();w3->raise();



    }
   if(ligneJ2 or colonneJ2 or diagoJ2())//si le J2 a fait une ligne , une diagonale ou un colonne , il a gagné
   {
       ui->label_2->setText("  Joueur 2  "); // voir + haut
       ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
       quiJoue=2;
       ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
         w->setVisible(true);
       w2->setVisible(true);
       w3->setVisible(true);
       w3->setText(" Victoire du Joueur 2");
       vPierre.value(0)->setEnabled(false);
       vPierre.value(1)->setEnabled(false);
       vPierre.value(2)->setEnabled(false);
       vPierre.value(3)->setEnabled(false);
       vPierre.value(4)->setEnabled(false);
       vPierre.value(5)->setEnabled(false);
       ui->pushButtonNewGame->setVisible(true);
       ui->pushButtonQuitter->setVisible(true);
       victoire->play();
       w->raise();w2->raise();w3->raise();



    }
    }

}

bool MainWindow::diagoJ1() // methoque qui renvoie true si un diagonale est remplie
{
    if((getNoByPoint(vPierre.value(0)->pos())==1 or getNoByPoint(vPierre.value(1)->pos())==1 or getNoByPoint(vPierre.value(2)->pos())==1) and (getNoByPoint(vPierre.value(0)->pos())==5 or getNoByPoint(vPierre.value(1)->pos())==5 or getNoByPoint(vPierre.value(2)->pos())==5) and (getNoByPoint(vPierre.value(0)->pos())==9 or getNoByPoint(vPierre.value(1)->pos())==9 or getNoByPoint(vPierre.value(2)->pos())==9)) // si les points sont 1 5 9 => diagonale
    {
        return true;
    }
    if((getNoByPoint(vPierre.value(0)->pos())==3 or getNoByPoint(vPierre.value(1)->pos())==3 or getNoByPoint(vPierre.value(2)->pos())==3) and (getNoByPoint(vPierre.value(0)->pos())==5 or getNoByPoint(vPierre.value(1)->pos())==5 or getNoByPoint(vPierre.value(2)->pos())==5) and (getNoByPoint(vPierre.value(0)->pos())==7 or getNoByPoint(vPierre.value(1)->pos())==7 or getNoByPoint(vPierre.value(2)->pos())==7))  // si les points sont 1 5 9 => diagonale
    {
        return true;
    }
    return false;
}
bool MainWindow::diagoJ2()// methoque qui renvoie true si un diagonale est remplie
{
    if((vPierre.value(3)->y()<plateauHauteur and vPierre.value(4)->y()<plateauHauteur and vPierre.value(5)->y()<plateauHauteur) and (getNoByPoint (vPierre.value(3)->pos())==1 or getNoByPoint (vPierre.value(4)->pos())==1 or getNoByPoint (vPierre.value(5)->pos())==1) and (getNoByPoint (vPierre.value(3)->pos())==5 or getNoByPoint (vPierre.value(4)->pos())==5 or getNoByPoint (vPierre.value(5)->pos())==5) and (getNoByPoint (vPierre.value(3)->pos())==9 or getNoByPoint (vPierre.value(4)->pos())==9 or getNoByPoint (vPierre.value(5)->pos())==9))
    {
        return true;
    }
    if((vPierre.value(3)->y()<plateauHauteur and vPierre.value(4)->y()<plateauHauteur and vPierre.value(5)->y()<plateauHauteur) and (getNoByPoint (vPierre.value(3)->pos())==3 or getNoByPoint (vPierre.value(4)->pos())==3 or getNoByPoint (vPierre.value(5)->pos())==3) and (getNoByPoint (vPierre.value(3)->pos())==5 or getNoByPoint (vPierre.value(4)->pos())==5 or getNoByPoint (vPierre.value(5)->pos())==5) and (getNoByPoint (vPierre.value(3)->pos())==7 or getNoByPoint (vPierre.value(4)->pos())==7 or getNoByPoint (vPierre.value(5)->pos())==7))
    {
        return true;
    }
    return false;
}


void MainWindow::GetVectorOuAller() // méthode qui rempli le vecteur des positions autorisée
{
    vAutorizedPoints.clear();
    vAutorizedPoints=ouAller(getNoPoint(vPierre.value(currentPierre-1)->pos()));


}
void MainWindow::creerTxtVictoire() // on crée les élément d'affichage lors de la victoire
{
     w=new QLabel(this);

       w->setGeometry(30,240,88,81);
        // On crée une vidéo. Ici, c'est un GIF
        QMovie * movie=new QMovie(":/Images/victoire.gif");
        // On l'associe à un label
        w->setMovie(movie);
        // On lance la vidéo
        movie->start();
        w->show(); // on a crée un gif
       w2=new QLabel(this);

           w2->setGeometry(365,240,88,81);
            // On crée une vidéo. Ici, c'est un GIF
            QMovie * movie2=new QMovie(":/Images/victoire.gif");
            // On l'associe à un label
            w2->setMovie(movie2);
            // On lance la vidéo
            movie2->start();
            w2->show();
        w3=new QLabel(this);
       w3->setStyleSheet("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));color:black;font: 63 italic 16pt");
       w3->setWordWrap(true);
       w3->setGeometry(125,240,235,141);
       w->setVisible(false);
       w2->setVisible(false);
       w3->setVisible(false); // on cache les elements tant qu'il n'y a pas de vainqueur
       w3->setAlignment(Qt::AlignCenter);

       ui->pushButtonNewGame->setVisible(false);
       ui->pushButtonQuitter->setVisible(false); // on cache les elements tant qu'il n'y a pas de vainqueur




}

void MainWindow::creerSon() // on créé les differents sons
{
//    fond=new QSoundEffect(this);
//    fond->setSource(QUrl::fromLocalFile(":/Images/marioF.wav"));
//    fond->setLoopCount(19);
//    fond->setVolume(0.8f);

    reussi=new QSoundEffect(this);
    reussi->setSource(QUrl::fromLocalFile(":/Images/yeees2.wav"));
    reussi->setLoopCount(1);
    reussi->setVolume(0.4f);

    dommage=new QSoundEffect(this);
    dommage->setSource(QUrl::fromLocalFile(":/Images/hooo2.wav"));
    dommage->setLoopCount(1);
    dommage->setVolume(0.8f);

    victoire=new QSoundEffect(this);
    victoire->setSource(QUrl::fromLocalFile(":/Images/victoire2.wav"));
    victoire->setLoopCount(1);
    victoire->setVolume(0.8f);

}

void MainWindow::gererTheme(int indicePlateau) // methode gere les themes selon l'indice du theme appelé (indicePlateau)
{
    if(indicePlateau==1) // si le theme appelé est celui du bois
    {
       ui->labelPlateau->setPixmap(QPixmap(":/Images/plateau.jpg").scaled(ui->labelPlateau->width(),ui->labelPlateau->height()));
        for(int i=0;i<vPierre.size();i++)
        {
            if(i<3)vPierre.value(i)->setPixmap(QPixmap(":/Images/pierre1.png").scaled(83,83));
            else vPierre.value(i)->setPixmap(QPixmap(":/Images/pierre2.png").scaled(83,83));
        }
        creerSon();



        currentTheme=1;

    }
    if(indicePlateau==2) // si le theme appelé est celui de l'herbe
    {
        ui->labelPlateau->setPixmap(QPixmap(":/Images/plateauHerbe.png").scaled(ui->labelPlateau->width(),ui->labelPlateau->height()));
        for(int i=0;i<vPierre.size();i++)
        {
            if(i<3)vPierre.value(i)->setPixmap(QPixmap(":/Images/golf1.png").scaled(83,83));
            else vPierre.value(i)->setPixmap(QPixmap(":/Images/golf2.png").scaled(83,83));
        }
        dommage->setSource(QUrl::fromLocalFile(":/Images/golfNon.wav"));
        reussi->setSource(QUrl::fromLocalFile(":/Images/golfOk.wav"));
        currentTheme=2;

    }
    if(indicePlateau==3) // si le theme appelé est celui du néon
    {
        ui->labelPlateau->setPixmap(QPixmap(":/Images/plateauNeon.png").scaled(ui->labelPlateau->width(),ui->labelPlateau->height()));
        for(int i=0;i<vPierre.size();i++)
        {
            if(i<3)vPierre.value(i)->setPixmap(QPixmap(":/Images/ring1.png").scaled(83,83));
            else vPierre.value(i)->setPixmap(QPixmap(":/Images/ring2.png").scaled(83,83));
        }
        dommage->setSource(QUrl::fromLocalFile(":/Images/neonNon.wav"));
        reussi->setSource(QUrl::fromLocalFile(":/Images/neonOk.wav"));

        currentTheme=3;

    }
    if(indicePlateau==4)
    {

        currentTheme=4;
       dommage->setSource(QUrl::fromLocalFile(":/Images/marioNon.wav"));
       victoire->setSource(QUrl::fromLocalFile(":/Images/mario-fin.wav"));
       reussi->setSource(QUrl::fromLocalFile(":/Images/marioOk.wav"));

        movieMario=new QMovie(":/Images/plateau-mario.gif");
        //movieMario->setSpeed(500);
        ui->labelPlateau->setMovie(movieMario);
      movieMario->start();
#ifdef ANDROID
        movieMario->stop();
        ui->labelPlateau->setPixmap(QPixmap(":/Images/plateau-mario.png").scaled(ui->labelPlateau->width(),ui->labelPlateau->height()));

#endif
      for(int i=0;i<vPierre.size();i++)
      {
          if(i<3)vPierre.value(i)->setPixmap(QPixmap(":/Images/mario1.png").scaled(83,83));
          else vPierre.value(i)->setPixmap(QPixmap(":/Images/mario2.png").scaled(83,83));
      }
    }
    else victoire->setSource(QUrl::fromLocalFile(":/Images/victoire2.wav"));

    if(indicePlateau==5) // si le theme appelé est celui du bois
    {
       ui->labelPlateau->setPixmap(QPixmap(":/Images/craft").scaled(ui->labelPlateau->width(),ui->labelPlateau->height()));
        for(int i=0;i<vPierre.size();i++)
        {
            if(i<3)vPierre.value(i)->setPixmap(QPixmap(":/Images/craft1").scaled(83,83));
            else vPierre.value(i)->setPixmap(QPixmap(":/Images/craft2").scaled(83,83));
        }
        creerSon();



        currentTheme=5;

    }

    ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
    for(int i=0;i<vPierre.size();i++)
    {
        vPierre.value(i)->setStyleSheet("background:rgba(0,0,0,0)");
    }

}

QPixmap MainWindow::getIconePLayer() // méthode qui revoie l'icone de joueur selon le currentTheme
{
    if(currentTheme==1)
    {
        if(quiJoue==1)return QPixmap(":/Images/pierre1.png");
        else return QPixmap(":/Images/pierre2.png");
    }
    if(currentTheme==2)
    {
        if(quiJoue==1)return QPixmap(":/Images/golf1.png");
        else return QPixmap(":/Images/golf2.png");
    }
    if(currentTheme==4)
    {
        if(quiJoue==1)return QPixmap(":/Images/mario1.png");
        else return QPixmap(":/Images/mario2.png");
    }
    if(currentTheme==5)
    {
        if(quiJoue==1)return QPixmap(":/Images/craft1");
        else return QPixmap(":/Images/craft2");
    }
    else
    {
        if(quiJoue==1)return QPixmap(":/Images/ring1.png");
        else return QPixmap(":/Images/ring2.png");
    }
}

void MainWindow::initialisation() // méthode qui initialise certain parametres au lancement
{
    quiJoue=1; // au J1 de Jouer
    ui->label_2->setText("   Joueur 1   ");
    ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
    doEvent=false; // par defaut un bouge pas
    gereDeplacement=0; // gere les doublon de déplacement
    plateauHauteur=ui->labelPlateau->height()+ui->labelPlateau->y()-vPierre.value(0)->height()/2;
    ordiJoue=true;

}
void MainWindow::defPoints() //méthode qui définie les points du plateau
{
    int widthPlat=ui->labelPlateau->width(); //variables qui vont simplifier les calculs
    int heightPlat=ui->labelPlateau->height();
    int xPlat=ui->labelPlateau->x();
    int yPLat=ui->labelPlateau->y();
    int widthPierre=vPierre.value(0)->width()/2;
    int heightPierre=vPierre.value(0)->height()/2;


    vPoint.clear();
    vPoint.push_back(QPoint(xPlat-widthPierre+widthPlat/5.2,yPLat-heightPierre+heightPlat/5.1)); // definition du point 1
     vPoint.push_back(QPoint(widthPlat/2+xPlat-widthPierre*1.07,yPLat-heightPierre+heightPlat/5.1));// definition du point 2
     vPoint.push_back(QPoint(widthPlat+xPlat-widthPierre*3.35,yPLat-heightPierre+heightPlat/5.1));// definition du point 3

     vPoint.push_back(QPoint(xPlat-widthPierre+widthPlat/5.2,heightPlat/2.018+yPLat-heightPierre));// definition du point 4
      vPoint.push_back(QPoint(widthPlat/2+xPlat-widthPierre*1.07,heightPlat/2.018+yPLat-heightPierre));// definition du point 5
      vPoint.push_back(QPoint(widthPlat+xPlat-widthPierre*3.35,heightPlat/2.018+yPLat-heightPierre));// definition du point 6

      vPoint.push_back(QPoint(xPlat-widthPierre+widthPlat/5.2,heightPlat+yPLat-heightPierre*3.32));// definition du point 7
       vPoint.push_back(QPoint(widthPlat/2+xPlat-widthPierre*1.07,heightPlat+yPLat-heightPierre*3.32));// definition du point 8
       vPoint.push_back(QPoint(widthPlat+xPlat-widthPierre*3.35,heightPlat+yPLat-heightPierre*3.32));// definition du point 9

}

void MainWindow::on_pushButtonNewGame_clicked() // si on veut rejouer
{
    victoire->stop(); //on stoppe la musique de victoire
    for(int i=0;i<vPierre.size();i++)
    {
        vPierre.value(i)->setEnabled(true); // on active les pierres
        if(i<3)vPierre.value(i)->setGeometry(-80+(i+1)*120,590,83,83);//et on les replace
        else vPierre.value(i)->setGeometry(-20+(i%3+1)*120,655,83,83);
    }
    quiJoue=1; // c est au joueur 1 de jouer
    ui->label_2->setText("  Joueur 1  ");
    ui->label_2->setStyleSheet("color : #CCC ;font: 63 italic 20pt 'URW Chancery L';background:rgba(0,0,0,0)");
    ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
    w->setVisible(false);
    w2->setVisible(false);
    w3->setVisible(false); // on met les affiche de victoire invisibles
    ui->pushButtonNewGame->setVisible(false);
    ui->pushButtonQuitter->setVisible(false);
    vPierre.value(3)->setHidden(false);
    vPierre.value(4)->setHidden(false); // on met les affiche de victoire invisibles
    vPierre.value(5)->setHidden(false);
    pierreBackground(false);


 }

void MainWindow::on_pushButtonQuitter_clicked() // si on veut quitter
{
    this->close();
}

void MainWindow::on_pushButtonThemes_clicked()// si on veut modifier le themes
{
    DialogTheme windowTheme(this); // on créée la fenetre de changement de themes
    windowTheme.exec();
}

void MainWindow::on_pushButtonNewGameHaut_clicked() // meme  code que + haut
{
    on_pushButtonNewGame_clicked();
}
void MainWindow::afficheOption()
{
    DialogOption windowOption(this); // on créée la fenetre de changement de themes
    windowOption.move(0,this->height()/8);
    windowOption.exec();
}
void MainWindow::on_pushButtonOptions_clicked()
{
    afficheOption();
}
//////////////////////////////DEBUT GESTION IA ///////////////////////////////////////
void MainWindow::gererOrdinateur()
{
    quiJoue=1;
     ui->labelIconPlayer->setPixmap(getIconePLayer().scaled(40,40));
     ui->label_2->setText("  Joueur 1");
     if(vPierre.value(5)->y()>plateauHauteur-20)
     {
         gerePlacementOrdi();
     }
     else
     {
         gereJeuOrdi();
     }

}
void MainWindow::gerePlacementOrdi()
{
    if(vPierre.value(3)->surLePLateau()==false)
    {
        if(placeLibre(4))vPierre.value(3)->move(vPoint.value(4));
        else vPierre.value(3)->move(vPoint.value(nbAletat(8,0,4)));
    }
    else
    {
        if(vPierre.value(4)->surLePLateau()==false)
        {
            if(checkIfJ1WillWon() and fautYAllerOrdi!=vPierre.value(3)->pos())vPierre.value(4)->move(fautYAllerOrdi);
            else
            {

             QVector <QPoint> vPointLibes;
             QVector <QPoint> vPointP1;
             for(int i=0;i<vPoint.size();i++)
             {
                 if(placeLibre(i))vPointLibes.push_back(vPoint.value(i));
             }
             for(int i=0;i<vPointLibes.size();i++)
             {
                 for(int n=0;n<ouAller(getNoByPoint(vPierre.value(3)->pos())).size();n++)
                 {
                     if(getNoByPoint(vPointLibes.value(i))==ouAller(getNoByPoint(vPierre.value(3)->pos())).value(n))
                     {
                         vPointP1.push_back(vPointLibes.value(i));
                     }
                 }
             }
             for(int i=0;i<vPointP1.size();i++)
             {
                getNoByPoint(vPointP1.value(i));
             }
             int nb=nbAletat(vPointP1.size()-1,0,-1);
                vPierre.value(4)->move(vPointLibes.value(nb));

            }
         }
        else
        {
            if(vPierre.value(5)->surLePLateau()==false)
            {

                goWinOrdiIfPOssible();
                if(ui->pushButtonNewGame->isVisible()!=true)//si personne n a encore gagné
                {
                     if(checkIfJ1WillWon2()==false)
                     {
                         OuallerOrditemp.clear();
                         for(int i=0;i<9;i++)
                         {
                             if(placeLibre(i))
                             {
                                 OuallerOrditemp.push_back(i);
                             }
                         }
                         vPierre.value(5)->move(vPoint.value(OuallerOrditemp.value(nbAletat(OuallerOrditemp.size()-1,0,-1))));
                     }

                }
            }
        }
    }
}


bool MainWindow::checkIfJ1WillWon2()
{
    int posP1=getNoByPoint(vPierre.value(0)->pos());
    int posP2=getNoByPoint(vPierre.value(1)->pos());
    int posP3=getNoByPoint(vPierre.value(2)->pos());

    if(vPierre.value(0)->x()==vPierre.value(1)->x() or vPierre.value(0)->x()==vPierre.value(2)->x() or vPierre.value(2)->x()==vPierre.value(1)->x())
    {


        if(vPierre.value(0)->x()!=vPierre.value(1)->x())
        {
            if(vPierre.value(0)->x()!=vPierre.value(2)->x())noPierreADeplacer_Ordi=0;
            else noPierreADeplacer_Ordi=1;
        }
        else noPierreADeplacer_Ordi=2;

        if((posP1==1 and posP2==4) or (posP1==1 and posP3==4) or (posP2==1 and posP3==4) or (posP2==1 and posP1==4) or (posP3==1 and posP1==4) or (posP3==1 and posP2==4))fautYAllerOrdi=vPoint.value(6);
        if((posP1==1 and posP2==7) or (posP1==1 and posP3==7) or (posP2==1 and posP3==7) or (posP2==1 and posP1==7) or (posP3==1 and posP1==7) or (posP3==1 and posP2==7))fautYAllerOrdi=vPoint.value(3);
        if((posP1==4 and posP2==7) or (posP1==4 and posP3==4) or (posP2==4 and posP3==7) or (posP2==4 and posP1==7) or (posP3==4 and posP1==4) or (posP3==4 and posP2==7))fautYAllerOrdi=vPoint.value(0);

        if((posP1==2 and posP2==5) or (posP1==2 and posP3==5) or (posP2==2 and posP3==5) or (posP2==2 and posP1==5) or (posP3==2 and posP1==5) or (posP3==2 and posP2==5))fautYAllerOrdi=vPoint.value(7);
        if((posP1==2 and posP2==8) or (posP1==2 and posP3==8) or (posP2==2 and posP3==8) or (posP2==2 and posP1==8) or (posP3==2 and posP1==8) or (posP3==2 and posP2==8))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==8) or (posP1==5 and posP3==8) or (posP2==5 and posP3==8) or (posP2==5 and posP1==8) or (posP3==5 and posP1==8) or (posP3==5 and posP2==8))fautYAllerOrdi=vPoint.value(1);

        if((posP1==3 and posP2==6) or (posP1==3 and posP3==6) or (posP2==3 and posP3==6) or (posP2==3 and posP1==6) or (posP3==3 and posP1==6) or (posP3==3 and posP2==6))fautYAllerOrdi=vPoint.value(8);
        if((posP1==3 and posP2==9) or (posP1==3 and posP3==9) or (posP2==3 and posP3==9) or (posP2==3 and posP1==9) or (posP3==3 and posP1==9) or (posP3==3 and posP2==9))fautYAllerOrdi=vPoint.value(5);
        if((posP1==6 and posP2==9) or (posP1==6 and posP3==9) or (posP2==6 and posP3==9) or (posP2==6 and posP1==9) or (posP3==6 and posP1==9) or (posP3==6 and posP2==9))fautYAllerOrdi=vPoint.value(2);



    }
    if(vPierre.value(0)->y()==vPierre.value(1)->y() or vPierre.value(0)->y()==vPierre.value(2)->y() or vPierre.value(2)->y()==vPierre.value(1)->y())
    {

        if(vPierre.value(0)->y()!=vPierre.value(1)->y())
        {
            if(vPierre.value(0)->y()!=vPierre.value(2)->y())noPierreADeplacer_Ordi=0;
            else noPierreADeplacer_Ordi=1;
        }
        else noPierreADeplacer_Ordi=2;


        if((posP1==1 and posP2==2) or (posP1==1 and posP3==2) or (posP2==1 and posP3==2) or (posP2==1 and posP1==2) or (posP3==1 and posP1==2) or (posP3==1 and posP2==2))fautYAllerOrdi=vPoint.value(2);
        if((posP1==1 and posP2==3) or (posP1==1 and posP3==3) or (posP2==1 and posP3==3) or (posP2==1 and posP1==3) or (posP3==1 and posP1==3) or (posP3==1 and posP2==3))fautYAllerOrdi=vPoint.value(0);
        if((posP1==2 and posP2==3) or (posP1==2 and posP3==3) or (posP2==2 and posP3==3) or (posP2==2 and posP1==3) or (posP3==2 and posP1==3) or (posP3==2 and posP2==3))fautYAllerOrdi=vPoint.value(1);

        if((posP1==4 and posP2==5) or (posP1==4 and posP3==5) or (posP2==4 and posP3==5) or (posP2==4 and posP1==5) or (posP3==4 and posP1==5) or (posP3==4 and posP2==5))fautYAllerOrdi=vPoint.value(5);
        if((posP1==4 and posP2==6) or (posP1==4 and posP3==6) or (posP2==4 and posP3==6) or (posP2==4 and posP1==6) or (posP3==4 and posP1==6) or (posP3==4 and posP2==6))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==6) or (posP1==5 and posP3==6) or (posP2==5 and posP3==6) or (posP2==5 and posP1==6) or (posP3==5 and posP1==6) or (posP3==5 and posP2==6))fautYAllerOrdi=vPoint.value(3);

        if((posP1==7 and posP2==8) or (posP1==7 and posP3==8) or (posP2==7 and posP3==8) or (posP2==7 and posP1==8) or (posP3==7 and posP1==8) or (posP3==7 and posP2==8))fautYAllerOrdi=vPoint.value(8);
        if((posP1==7 and posP2==9) or (posP1==7 and posP3==9) or (posP2==7 and posP3==9) or (posP2==7 and posP1==9) or (posP3==7 and posP1==9) or (posP3==7 and posP2==9))fautYAllerOrdi=vPoint.value(7);
        if((posP1==8 and posP2==9) or (posP1==8 and posP3==9) or (posP2==8 and posP3==9) or (posP2==8 and posP1==9) or (posP3==8 and posP1==9) or (posP3==8 and posP2==9))fautYAllerOrdi=vPoint.value(6);


    }

    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1))
    {
        vPierre.value(5)->move(vPoint.value(getNoByPoint(fautYAllerOrdi)-1));
        return true;
    }

    diagoJ1Ordi(0,1,2);
    bool j1PouuraYAller=false;
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).size();i++)
    {
        if(ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).value(i)==getNoByPoint(fautYAllerOrdi))j1PouuraYAller=true;
    }


     if(placeLibre(getNoByPoint(fautYAllerOrdi)-1) and j1PouuraYAller)
     {
          vPierre.value(5)->move(vPoint.value(getNoByPoint(fautYAllerOrdi)-1));
          return true;
     }

    return false;

}
bool MainWindow::checkIfJ1WillWon()
{
    int posP1=getNoByPoint(vPierre.value(0)->pos());
    int posP2=getNoByPoint(vPierre.value(1)->pos());
    int posP3=getNoByPoint(vPierre.value(2)->pos());

    if(vPierre.value(0)->x()==vPierre.value(1)->x() or vPierre.value(0)->x()==vPierre.value(2)->x() or vPierre.value(2)->x()==vPierre.value(1)->x())
    {
        if((posP1==1 and posP2==4) or (posP1==1 and posP3==4) or (posP2==1 and posP3==4) or (posP2==1 and posP1==4) or (posP3==1 and posP1==4) or (posP3==1 and posP2==4))fautYAllerOrdi=vPoint.value(6);
        if((posP1==1 and posP2==7) or (posP1==1 and posP3==7) or (posP2==1 and posP3==7) or (posP2==1 and posP1==7) or (posP3==1 and posP1==7) or (posP3==1 and posP2==7))fautYAllerOrdi=vPoint.value(3);
        if((posP1==4 and posP2==7) or (posP1==4 and posP3==4) or (posP2==4 and posP3==7) or (posP2==4 and posP1==7) or (posP3==4 and posP1==4) or (posP3==4 and posP2==7))fautYAllerOrdi=vPoint.value(0);

        if((posP1==2 and posP2==5) or (posP1==2 and posP3==5) or (posP2==2 and posP3==5) or (posP2==2 and posP1==5) or (posP3==2 and posP1==5) or (posP3==2 and posP2==5))fautYAllerOrdi=vPoint.value(7);
        if((posP1==2 and posP2==8) or (posP1==2 and posP3==8) or (posP2==2 and posP3==8) or (posP2==2 and posP1==8) or (posP3==2 and posP1==8) or (posP3==2 and posP2==8))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==8) or (posP1==5 and posP3==8) or (posP2==5 and posP3==8) or (posP2==5 and posP1==8) or (posP3==5 and posP1==8) or (posP3==5 and posP2==8))fautYAllerOrdi=vPoint.value(1);

        if((posP1==3 and posP2==6) or (posP1==3 and posP3==6) or (posP2==3 and posP3==6) or (posP2==3 and posP1==6) or (posP3==3 and posP1==6) or (posP3==3 and posP2==6))fautYAllerOrdi=vPoint.value(8);
        if((posP1==3 and posP2==9) or (posP1==3 and posP3==9) or (posP2==3 and posP3==9) or (posP2==3 and posP1==9) or (posP3==3 and posP1==9) or (posP3==3 and posP2==9))fautYAllerOrdi=vPoint.value(5);
        if((posP1==6 and posP2==9) or (posP1==6 and posP3==9) or (posP2==6 and posP3==9) or (posP2==6 and posP1==9) or (posP3==6 and posP1==9) or (posP3==6 and posP2==9))fautYAllerOrdi=vPoint.value(2);
        return true;
    }
    if(vPierre.value(0)->y()==vPierre.value(1)->y() or vPierre.value(0)->y()==vPierre.value(2)->y() or vPierre.value(2)->y()==vPierre.value(1)->y())
    {

        if((posP1==1 and posP2==2) or (posP1==1 and posP3==2) or (posP2==1 and posP3==2) or (posP2==1 and posP1==2) or (posP3==1 and posP1==2) or (posP3==1 and posP2==2))fautYAllerOrdi=vPoint.value(2);
        if((posP1==1 and posP2==3) or (posP1==1 and posP3==3) or (posP2==1 and posP3==3) or (posP2==1 and posP1==3) or (posP3==1 and posP1==3) or (posP3==1 and posP2==3))fautYAllerOrdi=vPoint.value(0);
        if((posP1==2 and posP2==3) or (posP1==2 and posP3==3) or (posP2==2 and posP3==3) or (posP2==2 and posP1==3) or (posP3==2 and posP1==3) or (posP3==2 and posP2==3))fautYAllerOrdi=vPoint.value(1);

        if((posP1==4 and posP2==5) or (posP1==4 and posP3==5) or (posP2==4 and posP3==5) or (posP2==4 and posP1==5) or (posP3==4 and posP1==5) or (posP3==4 and posP2==5))fautYAllerOrdi=vPoint.value(5);
        if((posP1==4 and posP2==6) or (posP1==4 and posP3==6) or (posP2==4 and posP3==6) or (posP2==4 and posP1==6) or (posP3==4 and posP1==6) or (posP3==4 and posP2==6))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==6) or (posP1==5 and posP3==6) or (posP2==5 and posP3==6) or (posP2==5 and posP1==6) or (posP3==5 and posP1==6) or (posP3==5 and posP2==6))fautYAllerOrdi=vPoint.value(3);

        if((posP1==7 and posP2==8) or (posP1==7 and posP3==8) or (posP2==7 and posP3==8) or (posP2==7 and posP1==8) or (posP3==7 and posP1==8) or (posP3==7 and posP2==8))fautYAllerOrdi=vPoint.value(8);
        if((posP1==7 and posP2==9) or (posP1==7 and posP3==9) or (posP2==7 and posP3==9) or (posP2==7 and posP1==9) or (posP3==7 and posP1==9) or (posP3==7 and posP2==9))fautYAllerOrdi=vPoint.value(7);
        if((posP1==8 and posP2==9) or (posP1==8 and posP3==9) or (posP2==8 and posP3==9) or (posP2==8 and posP1==9) or (posP3==8 and posP1==9) or (posP3==8 and posP2==9))fautYAllerOrdi=vPoint.value(6);

        return true;
    }
    return diagoJ1Ordi(0,1,2);
}

void MainWindow::goWinOrdiIfPOssible()
{
    int posPO1=getNoByPoint(vPierre.value(3)->pos());
    int posPO2=getNoByPoint(vPierre.value(4)->pos());
    if(vPierre.value(3)->x()==vPierre.value(4)->x())
    {

        if(posPO1==1 and posPO2==4 or (posPO1==4 and posPO2==1))fautYAllerOrdi=vPoint.value(6);
        if(posPO1==1 and posPO2==7 or (posPO1==7 and posPO2==1))fautYAllerOrdi=vPoint.value(3);
        if(posPO1==4 and posPO2==7 or (posPO1==7 and posPO2==4))fautYAllerOrdi=vPoint.value(0);

        if(posPO1==2 and posPO2==5 or (posPO1==5 and posPO2==2))fautYAllerOrdi=vPoint.value(7);
        if(posPO1==2 and posPO2==8 or (posPO1==8 and posPO2==2))fautYAllerOrdi=vPoint.value(4);
        if(posPO1==5 and posPO2==8 or (posPO1==8 and posPO2==5))fautYAllerOrdi=vPoint.value(1);

        if(posPO1==3 and posPO2==6 or (posPO1==6 and posPO2==3))fautYAllerOrdi=vPoint.value(8);
        if(posPO1==3 and posPO2==9 or (posPO1==9 and posPO2==3))fautYAllerOrdi=vPoint.value(5);
        if(posPO1==6 and posPO2==9 or (posPO1==9 and posPO2==6))fautYAllerOrdi=vPoint.value(2);

    }
    if(vPierre.value(3)->y()==vPierre.value(4)->y())
    {

        if(posPO1==1 and posPO2==2 or (posPO1==2 and posPO2==1))fautYAllerOrdi=vPoint.value(2);
        if(posPO1==1 and posPO2==3 or (posPO1==3 and posPO2==1))fautYAllerOrdi=vPoint.value(1);
        if(posPO1==2 and posPO2==3 or (posPO1==3 and posPO2==2))fautYAllerOrdi=vPoint.value(0);

        if(posPO1==4 and posPO2==5 or (posPO1==5 and posPO2==4))fautYAllerOrdi=vPoint.value(5);
        if(posPO1==4 and posPO2==6 or (posPO1==6 and posPO2==4))fautYAllerOrdi=vPoint.value(4);
        if(posPO1==5 and posPO2==6 or (posPO1==6 and posPO2==5))fautYAllerOrdi=vPoint.value(3);

        if(posPO1==7 and posPO2==8 or (posPO1==8 and posPO2==7))fautYAllerOrdi=vPoint.value(8);
        if(posPO1==7 and posPO2==9 or (posPO1==9 and posPO2==7))fautYAllerOrdi=vPoint.value(7);
        if(posPO1==8 and posPO2==9 or (posPO1==9 and posPO2==8))fautYAllerOrdi=vPoint.value(6);

    }
       if(posPO1==5)
        {
        if(posPO2==1)fautYAllerOrdi=vPoint.value(8);
        if(posPO2==2)fautYAllerOrdi=vPoint.value(7);
        if(posPO2==3)fautYAllerOrdi=vPoint.value(6);
        if(posPO2==4)fautYAllerOrdi=vPoint.value(5);
        if(posPO2==6)fautYAllerOrdi=vPoint.value(3);
        if(posPO2==7)fautYAllerOrdi=vPoint.value(2);
        if(posPO2==8)fautYAllerOrdi=vPoint.value(1);
        if(posPO2==9)fautYAllerOrdi=vPoint.value(0);
        }



    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1))
    {
        vPierre.value(5)->move(fautYAllerOrdi);
        checkIfWinner();
    }

}
bool MainWindow::diagoJ1Ordi(int n1,int n2,int n3)
{
    int posP1=getNoByPoint(vPierre.value(n1)->pos());
    int posP2=getNoByPoint(vPierre.value(n2)->pos());
    int posP3=getNoByPoint(vPierre.value(n3)->pos());


    if(posP1%2==0)noPierreADeplacer_Ordi=0;if(posP2%2==0)noPierreADeplacer_Ordi=1;if(posP3%2==0)noPierreADeplacer_Ordi=2;
    if(posP1==5)
    {
        switch (posP2) {
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;

        }

        switch (posP3) {
        case -1:break;
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;
        }

        if(getNoByPoint(fautYAllerOrdi)!=-1) return true;
    }
    if(posP2==5)
    {
        switch (posP1) {
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;
        }
        switch (posP3) {
        case -1:break;
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;
        }

        if(getNoByPoint(fautYAllerOrdi)!=-1) return true;

    }
    if(posP3==5)
    {
        switch (posP1) {
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;

        }
        switch (posP2) {
        case -1:break;
        case 1:if(placeLibre(8))fautYAllerOrdi=vPoint.value(8);break;
        case 2:if(placeLibre(7))fautYAllerOrdi=vPoint.value(7);break;
        case 3:if(placeLibre(6))fautYAllerOrdi=vPoint.value(6);break;
        case 4:if(placeLibre(5))fautYAllerOrdi=vPoint.value(5);break;
        case 6:if(placeLibre(3))fautYAllerOrdi=vPoint.value(3);break;
        case 7:if(placeLibre(2))fautYAllerOrdi=vPoint.value(2);break;
        case 8:if(placeLibre(1))fautYAllerOrdi=vPoint.value(1);break;
        case 9:if(placeLibre(0))fautYAllerOrdi=vPoint.value(0);break;

        }

        if(getNoByPoint(fautYAllerOrdi)!=-1) return true;
    }

    return false;
}

void MainWindow::gereJeuOrdi()
{
        if(goWinOrdiIfPOssibleJeu()==false)
        {
            if(checkIfJ1WillWonJeu()==false)
            {
                GoRandomPLaceJeu();
            }
        }
}
bool MainWindow::GoRandomPLaceJeu()
{
    QVector <QPoint> vPointsLibres;
    QVector <int> destP1;
    QVector <int> destP2;
    QVector <int> destP3;
    for(int i=0;i<vPoint.size();i++)
    {
        if(placeLibre(i))
        {

            vPointsLibres.push_back(vPoint.value(i));
        }
    }
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(3)->pos())).size();i++)
    {
        for(int n=0;n<vPointsLibres.size();n++)
        {
            if(ouAller(getNoByPoint(vPierre.value(3)->pos())).value(i)==getNoByPoint(vPointsLibres.value(n)))destP1.push_back(getNoByPoint(vPointsLibres.value(n)));
        }
    }
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(4)->pos())).size();i++)
    {
        for(int n=0;n<vPointsLibres.size();n++)
        {
            if(ouAller(getNoByPoint(vPierre.value(4)->pos())).value(i)==getNoByPoint(vPointsLibres.value(n)))destP2.push_back(getNoByPoint(vPointsLibres.value(n)));

        }
    }
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(5)->pos())).size();i++)
    {
        for(int n=0;n<vPointsLibres.size();n++)
        {
            if(ouAller(getNoByPoint(vPierre.value(5)->pos())).value(i)==getNoByPoint(vPointsLibres.value(n)))destP3.push_back(getNoByPoint(vPointsLibres.value(n)));
        }
    }
     int nbA1;
     int size;
    do {
        nbA1=nbAletat(2,0,-1);
        if(nbA1==0)size=destP1.size();
        if(nbA1==1)size=destP2.size();
        if(nbA1==2)size=destP3.size();

    } while (!(size>0));
    if(nbA1==0 and destP1.size()>0)
    {
        vPierre.value(3)->move(vPoint.value(destP1.value(destP1.size()-1)-1));
    }
    if(nbA1==1 and destP2.size()>0)vPierre.value(4)->move(vPoint.value(destP2.value(destP2.size()-1)-1));
    if(nbA1==2 and destP3.size()>0)vPierre.value(5)->move(vPoint.value(destP3.value(0)-1));
    checkIfWinner();

    return true;
}
bool MainWindow::goWinOrdiIfPOssibleJeu()
{
    int posP1=getNoByPoint(vPierre.value(3)->pos());
    int posP2=getNoByPoint(vPierre.value(4)->pos());
    int posP3=getNoByPoint(vPierre.value(5)->pos());

    if(vPierre.value(3)->x()==vPierre.value(4)->x() or vPierre.value(3)->x()==vPierre.value(5)->x() or vPierre.value(5)->x()==vPierre.value(4)->x())
    {


        if(vPierre.value(3)->x()!=vPierre.value(4)->x())
        {
            if(vPierre.value(3)->x()!=vPierre.value(5)->x())noPierreADeplacer_Ordi=3;
            else noPierreADeplacer_Ordi=4;
        }
        else noPierreADeplacer_Ordi=5;

        if((posP1==1 and posP2==4) or (posP1==1 and posP3==4) or (posP2==1 and posP3==4) or (posP2==1 and posP1==4) or (posP3==1 and posP1==4) or (posP3==1 and posP2==4))fautYAllerOrdi=vPoint.value(6);
        if((posP1==1 and posP2==7) or (posP1==1 and posP3==7) or (posP2==1 and posP3==7) or (posP2==1 and posP1==7) or (posP3==1 and posP1==7) or (posP3==1 and posP2==7))fautYAllerOrdi=vPoint.value(3);
        if((posP1==4 and posP2==7) or (posP1==4 and posP3==4) or (posP2==4 and posP3==7) or (posP2==4 and posP1==7) or (posP3==4 and posP1==4) or (posP3==4 and posP2==7))fautYAllerOrdi=vPoint.value(0);

        if((posP1==2 and posP2==5) or (posP1==2 and posP3==5) or (posP2==2 and posP3==5) or (posP2==2 and posP1==5) or (posP3==2 and posP1==5) or (posP3==2 and posP2==5))fautYAllerOrdi=vPoint.value(7);
        if((posP1==2 and posP2==8) or (posP1==2 and posP3==8) or (posP2==2 and posP3==8) or (posP2==2 and posP1==8) or (posP3==2 and posP1==8) or (posP3==2 and posP2==8))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==8) or (posP1==5 and posP3==8) or (posP2==5 and posP3==8) or (posP2==5 and posP1==8) or (posP3==5 and posP1==8) or (posP3==5 and posP2==8))fautYAllerOrdi=vPoint.value(1);

        if((posP1==3 and posP2==6) or (posP1==3 and posP3==6) or (posP2==3 and posP3==6) or (posP2==3 and posP1==6) or (posP3==3 and posP1==6) or (posP3==3 and posP2==6))fautYAllerOrdi=vPoint.value(8);
        if((posP1==3 and posP2==9) or (posP1==3 and posP3==9) or (posP2==3 and posP3==9) or (posP2==3 and posP1==9) or (posP3==3 and posP1==9) or (posP3==3 and posP2==9))fautYAllerOrdi=vPoint.value(5);
        if((posP1==6 and posP2==9) or (posP1==6 and posP3==9) or (posP2==6 and posP3==9) or (posP2==6 and posP1==9) or (posP3==6 and posP1==9) or (posP3==6 and posP2==9))fautYAllerOrdi=vPoint.value(2);



    }
    if(vPierre.value(3)->y()==vPierre.value(4)->y() or vPierre.value(3)->y()==vPierre.value(5)->y() or vPierre.value(5)->y()==vPierre.value(4)->y())
    {

        if(vPierre.value(3)->y()!=vPierre.value(4)->y())
        {
            if(vPierre.value(3)->y()!=vPierre.value(5)->y())noPierreADeplacer_Ordi=3;
            else noPierreADeplacer_Ordi=4;
        }
        else noPierreADeplacer_Ordi=5;


        if((posP1==1 and posP2==2) or (posP1==1 and posP3==2) or (posP2==1 and posP3==2) or (posP2==1 and posP1==2) or (posP3==1 and posP1==2) or (posP3==1 and posP2==2))fautYAllerOrdi=vPoint.value(2);
        if((posP1==1 and posP2==3) or (posP1==1 and posP3==3) or (posP2==1 and posP3==3) or (posP2==1 and posP1==3) or (posP3==1 and posP1==3) or (posP3==1 and posP2==3))fautYAllerOrdi=vPoint.value(0);
        if((posP1==2 and posP2==3) or (posP1==2 and posP3==3) or (posP2==2 and posP3==3) or (posP2==2 and posP1==3) or (posP3==2 and posP1==3) or (posP3==2 and posP2==3))fautYAllerOrdi=vPoint.value(1);

        if((posP1==4 and posP2==5) or (posP1==4 and posP3==5) or (posP2==4 and posP3==5) or (posP2==4 and posP1==5) or (posP3==4 and posP1==5) or (posP3==4 and posP2==5))fautYAllerOrdi=vPoint.value(5);
        if((posP1==4 and posP2==6) or (posP1==4 and posP3==6) or (posP2==4 and posP3==6) or (posP2==4 and posP1==6) or (posP3==4 and posP1==6) or (posP3==4 and posP2==6))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==6) or (posP1==5 and posP3==6) or (posP2==5 and posP3==6) or (posP2==5 and posP1==6) or (posP3==5 and posP1==6) or (posP3==5 and posP2==6))fautYAllerOrdi=vPoint.value(3);

        if((posP1==7 and posP2==8) or (posP1==7 and posP3==8) or (posP2==7 and posP3==8) or (posP2==7 and posP1==8) or (posP3==7 and posP1==8) or (posP3==7 and posP2==8))fautYAllerOrdi=vPoint.value(8);
        if((posP1==7 and posP2==9) or (posP1==7 and posP3==9) or (posP2==7 and posP3==9) or (posP2==7 and posP1==9) or (posP3==7 and posP1==9) or (posP3==7 and posP2==9))fautYAllerOrdi=vPoint.value(7);
        if((posP1==8 and posP2==9) or (posP1==8 and posP3==9) or (posP2==8 and posP3==9) or (posP2==8 and posP1==9) or (posP3==8 and posP1==9) or (posP3==8 and posP2==9))fautYAllerOrdi=vPoint.value(6);


    }
    bool OrdiCanGo=false;
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).size();i++)
    {
        if(ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).value(i)==getNoByPoint(fautYAllerOrdi))OrdiCanGo=true;
    }
    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1) and OrdiCanGo)
    {
        vPierre.value(noPierreADeplacer_Ordi)->move(fautYAllerOrdi);
        checkIfWinner();
        return true;
    }
    OrdiCanGo=false;
    diagoJ1Ordi(3,4,5);
    if(posP1%2==0)noPierreADeplacer_Ordi=3;if(posP2%2==0)noPierreADeplacer_Ordi=4;if(posP3%2==0)noPierreADeplacer_Ordi=5;
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).size();i++)
    {
        if(ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).value(i)==getNoByPoint(fautYAllerOrdi))OrdiCanGo=true;
    }
    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1) and OrdiCanGo)
    {
        vPierre.value(noPierreADeplacer_Ordi)->move(fautYAllerOrdi);
        checkIfWinner();
        return true;
    }
    return false;

}


bool MainWindow::checkIfJ1WillWonJeu()
{
    int posP1=getNoByPoint(vPierre.value(0)->pos());
    int posP2=getNoByPoint(vPierre.value(1)->pos());
    int posP3=getNoByPoint(vPierre.value(2)->pos());

    if(vPierre.value(0)->x()==vPierre.value(1)->x() or vPierre.value(0)->x()==vPierre.value(2)->x() or vPierre.value(2)->x()==vPierre.value(1)->x())
    {


        if(vPierre.value(0)->x()!=vPierre.value(1)->x())
        {
            if(vPierre.value(0)->x()!=vPierre.value(2)->x())noPierreADeplacer_Ordi=0;
            else noPierreADeplacer_Ordi=1;
        }
        else noPierreADeplacer_Ordi=2;

        if((posP1==1 and posP2==4) or (posP1==1 and posP3==4) or (posP2==1 and posP3==4) or (posP2==1 and posP1==4) or (posP3==1 and posP1==4) or (posP3==1 and posP2==4))fautYAllerOrdi=vPoint.value(6);
        if((posP1==1 and posP2==7) or (posP1==1 and posP3==7) or (posP2==1 and posP3==7) or (posP2==1 and posP1==7) or (posP3==1 and posP1==7) or (posP3==1 and posP2==7))fautYAllerOrdi=vPoint.value(3);
        if((posP1==4 and posP2==7) or (posP1==4 and posP3==4) or (posP2==4 and posP3==7) or (posP2==4 and posP1==7) or (posP3==4 and posP1==4) or (posP3==4 and posP2==7))fautYAllerOrdi=vPoint.value(0);

        if((posP1==2 and posP2==5) or (posP1==2 and posP3==5) or (posP2==2 and posP3==5) or (posP2==2 and posP1==5) or (posP3==2 and posP1==5) or (posP3==2 and posP2==5))fautYAllerOrdi=vPoint.value(7);
        if((posP1==2 and posP2==8) or (posP1==2 and posP3==8) or (posP2==2 and posP3==8) or (posP2==2 and posP1==8) or (posP3==2 and posP1==8) or (posP3==2 and posP2==8))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==8) or (posP1==5 and posP3==8) or (posP2==5 and posP3==8) or (posP2==5 and posP1==8) or (posP3==5 and posP1==8) or (posP3==5 and posP2==8))fautYAllerOrdi=vPoint.value(1);

        if((posP1==3 and posP2==6) or (posP1==3 and posP3==6) or (posP2==3 and posP3==6) or (posP2==3 and posP1==6) or (posP3==3 and posP1==6) or (posP3==3 and posP2==6))fautYAllerOrdi=vPoint.value(8);
        if((posP1==3 and posP2==9) or (posP1==3 and posP3==9) or (posP2==3 and posP3==9) or (posP2==3 and posP1==9) or (posP3==3 and posP1==9) or (posP3==3 and posP2==9))fautYAllerOrdi=vPoint.value(5);
        if((posP1==6 and posP2==9) or (posP1==6 and posP3==9) or (posP2==6 and posP3==9) or (posP2==6 and posP1==9) or (posP3==6 and posP1==9) or (posP3==6 and posP2==9))fautYAllerOrdi=vPoint.value(2);



    }
    if(vPierre.value(0)->y()==vPierre.value(1)->y() or vPierre.value(0)->y()==vPierre.value(2)->y() or vPierre.value(2)->y()==vPierre.value(1)->y())
    {

        if(vPierre.value(0)->y()!=vPierre.value(1)->y())
        {
            if(vPierre.value(0)->y()!=vPierre.value(2)->y())noPierreADeplacer_Ordi=0;
            else noPierreADeplacer_Ordi=1;
        }
        else noPierreADeplacer_Ordi=2;


        if((posP1==1 and posP2==2) or (posP1==1 and posP3==2) or (posP2==1 and posP3==2) or (posP2==1 and posP1==2) or (posP3==1 and posP1==2) or (posP3==1 and posP2==2))fautYAllerOrdi=vPoint.value(2);
        if((posP1==1 and posP2==3) or (posP1==1 and posP3==3) or (posP2==1 and posP3==3) or (posP2==1 and posP1==3) or (posP3==1 and posP1==3) or (posP3==1 and posP2==3))fautYAllerOrdi=vPoint.value(0);
        if((posP1==2 and posP2==3) or (posP1==2 and posP3==3) or (posP2==2 and posP3==3) or (posP2==2 and posP1==3) or (posP3==2 and posP1==3) or (posP3==2 and posP2==3))fautYAllerOrdi=vPoint.value(1);

        if((posP1==4 and posP2==5) or (posP1==4 and posP3==5) or (posP2==4 and posP3==5) or (posP2==4 and posP1==5) or (posP3==4 and posP1==5) or (posP3==4 and posP2==5))fautYAllerOrdi=vPoint.value(5);
        if((posP1==4 and posP2==6) or (posP1==4 and posP3==6) or (posP2==4 and posP3==6) or (posP2==4 and posP1==6) or (posP3==4 and posP1==6) or (posP3==4 and posP2==6))fautYAllerOrdi=vPoint.value(4);
        if((posP1==5 and posP2==6) or (posP1==5 and posP3==6) or (posP2==5 and posP3==6) or (posP2==5 and posP1==6) or (posP3==5 and posP1==6) or (posP3==5 and posP2==6))fautYAllerOrdi=vPoint.value(3);

        if((posP1==7 and posP2==8) or (posP1==7 and posP3==8) or (posP2==7 and posP3==8) or (posP2==7 and posP1==8) or (posP3==7 and posP1==8) or (posP3==7 and posP2==8))fautYAllerOrdi=vPoint.value(8);
        if((posP1==7 and posP2==9) or (posP1==7 and posP3==9) or (posP2==7 and posP3==9) or (posP2==7 and posP1==9) or (posP3==7 and posP1==9) or (posP3==7 and posP2==9))fautYAllerOrdi=vPoint.value(7);
        if((posP1==8 and posP2==9) or (posP1==8 and posP3==9) or (posP2==8 and posP3==9) or (posP2==8 and posP1==9) or (posP3==8 and posP1==9) or (posP3==8 and posP2==9))fautYAllerOrdi=vPoint.value(6);


    }
    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1))
    {
        bool dejaAlle=false;
        for(int i=3;i<vPierre.size();i++)
        {
            for(int n=0;n<ouAller(getNoByPoint(vPierre.value(i)->pos())).size();n++)
            {
                if(ouAller(getNoByPoint(vPierre.value(i)->pos())).value(n)==getNoByPoint(fautYAllerOrdi) and dejaAlle==false)
                {
                    vPierre.value(i)->move(fautYAllerOrdi);
                    return true;
                }
            }
        }

    }

    diagoJ1Ordi(0,1,2);
    bool j1PouuraYAller=false;
    for(int i=0;i<ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).size();i++)
    {
        if(ouAller(getNoByPoint(vPierre.value(noPierreADeplacer_Ordi)->pos())).value(i)==getNoByPoint(fautYAllerOrdi))j1PouuraYAller=true;
    }


    if(placeLibre(getNoByPoint(fautYAllerOrdi)-1))
    {
        bool dejaAlle=false;
        for(int i=3;i<vPierre.size();i++)
        {
            for(int n=0;n<ouAller(getNoByPoint(vPierre.value(i)->pos())).size();n++)
            {
                if(ouAller(getNoByPoint(vPierre.value(i)->pos())).value(n)==getNoByPoint(fautYAllerOrdi) and dejaAlle==false)
                {
                    vPierre.value(i)->move(fautYAllerOrdi);
                    return true;
                }
            }
        }

    }

    return false;

}

int MainWindow::nbAletat(int nbMax, int nbMin , int valeurInterdite)
{
    srand(time(NULL));
    int nombreMystere ;
    do{
        nombreMystere = (rand()%(nbMax - nbMin +1 )) + nbMin;
    }
    while((nombreMystere)==valeurInterdite);
    return nombreMystere;
}
bool MainWindow::placeLibre(int noPlace)
{
    for(int i=0;i<vPierre.size();i++)
    {
        if(vPierre.value(i)->pos()==getPOintByNo(noPlace))return false;
    }
    return true;
}
QPoint MainWindow::getPOintByNo(int no)
{
    return vPoint.value(no);
}
