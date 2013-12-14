#include "dialogtheme.h"
#include "ui_dialogtheme.h"

DialogTheme::DialogTheme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTheme)
{
    ui->setupUi(this);

}

DialogTheme::~DialogTheme()
{
    delete ui;
}

void DialogTheme::on_pushButtonThemeBois_clicked() // si on veut le theme bois
{

    ((MainWindow *)parent())->gererTheme(1); // on change le theme
    this->close();

}

void DialogTheme::on_pushButtonThemeHerbe_clicked() // si on veut le theme herbe
{
    ((MainWindow *)parent())->gererTheme(2);  // on change le theme
    this->close();
}
void DialogTheme::on_pushButtonThemeNeon_clicked() // si on veut le theme neon
{
    ((MainWindow *)parent())->gererTheme(3);  // on change le theme
    this->close();
}

void DialogTheme::on_pushButtonThemeMario_clicked()
{
    ((MainWindow *)parent())->gererTheme(4);  // on change le theme
    this->close();
}

void DialogTheme::on_pushButtonThemeMinecraft_clicked()
{
    ((MainWindow *)parent())->gererTheme(5);  // on change le theme
    this->close();
}
