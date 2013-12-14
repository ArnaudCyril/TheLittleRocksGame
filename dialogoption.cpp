#include "dialogoption.h"
#include "ui_dialogoption.h"
#include "mainwindow.h"
DialogOption::DialogOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOption)
{
    ui->setupUi(this);
}

DialogOption::~DialogOption()
{
    delete ui;
}

void DialogOption::on_pushButtonOrdi_clicked()
{
    ((MainWindow *)parent())->ordiJoue=true;
    ((MainWindow *)parent())->on_pushButtonNewGame_clicked();
    this->close();
}

void DialogOption::on_pushButtonJ1J2_clicked()
{
    ((MainWindow *)parent())->ordiJoue=false;
    ((MainWindow *)parent())->on_pushButtonNewGame_clicked();
    this->close();
}
