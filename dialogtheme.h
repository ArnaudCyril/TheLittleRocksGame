#ifndef DIALOGTHEME_H
#define DIALOGTHEME_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class DialogTheme;
}

class DialogTheme : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTheme(QWidget *parent = 0);
    ~DialogTheme();

public slots:
    void on_pushButtonThemeBois_clicked(); // les slots du dialogTheme

    void on_pushButtonThemeHerbe_clicked();

    void on_pushButtonThemeNeon_clicked();

private slots:
    void on_pushButtonThemeMario_clicked();

    void on_pushButtonThemeMinecraft_clicked();

private:
    Ui::DialogTheme *ui;

};

#endif // DIALOGTHEME_H

