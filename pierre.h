#ifndef PIERRE_H
#define PIERRE_H

#include <QLabel>
#include <QMouseEvent>
class pierre : public QLabel
{
    Q_OBJECT
public:
    explicit pierre(QWidget *parent = 0,int i=0);
    void mousePressEvent(QMouseEvent *ev); // quand on clique sur une pierre
    int noPierre; // le numero de la pierre
    bool surLePLateau(); // true si la pierre est sur le plateau

signals:

public slots:

};

#endif // PIERRE_H
