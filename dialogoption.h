#ifndef DIALOGOPTION_H
#define DIALOGOPTION_H

#include <QDialog>

namespace Ui {
class DialogOption;
}

class DialogOption : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOption(QWidget *parent = 0);
    ~DialogOption();

private slots:
    void on_pushButtonOrdi_clicked();

    void on_pushButtonJ1J2_clicked();

private:
    Ui::DialogOption *ui;
};

#endif // DIALOGOPTION_H
