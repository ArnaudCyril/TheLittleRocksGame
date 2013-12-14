/********************************************************************************
** Form generated from reading UI file 'dialogoption.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOPTION_H
#define UI_DIALOGOPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogOption
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonOrdi;
    QPushButton *pushButtonJ1J2;

    void setupUi(QDialog *DialogOption)
    {
        if (DialogOption->objectName().isEmpty())
            DialogOption->setObjectName(QStringLiteral("DialogOption"));
        DialogOption->resize(488, 373);
        DialogOption->setStyleSheet(QStringLiteral("background-color: rgb(89, 89, 89);"));
        verticalLayout_2 = new QVBoxLayout(DialogOption);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonOrdi = new QPushButton(DialogOption);
        pushButtonOrdi->setObjectName(QStringLiteral("pushButtonOrdi"));
        pushButtonOrdi->setMinimumSize(QSize(0, 120));
        pushButtonOrdi->setStyleSheet(QLatin1String("background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 100, 255, 255), stop:1 rgba(255, 255, 255, 255));\n"
"font: 63 italic 18pt 'URW Chancery L'"));

        verticalLayout->addWidget(pushButtonOrdi);

        pushButtonJ1J2 = new QPushButton(DialogOption);
        pushButtonJ1J2->setObjectName(QStringLiteral("pushButtonJ1J2"));
        pushButtonJ1J2->setMinimumSize(QSize(0, 120));
        pushButtonJ1J2->setMaximumSize(QSize(16777215, 16777215));
        pushButtonJ1J2->setStyleSheet(QLatin1String("background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 100, 255, 255), stop:1 rgba(255, 255, 255, 255));\n"
"font: 63 italic 18pt 'URW Chancery L'"));

        verticalLayout->addWidget(pushButtonJ1J2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogOption);

        QMetaObject::connectSlotsByName(DialogOption);
    } // setupUi

    void retranslateUi(QDialog *DialogOption)
    {
        DialogOption->setWindowTitle(QApplication::translate("DialogOption", "Choix du mode de jeu", 0));
        pushButtonOrdi->setText(QApplication::translate("DialogOption", "Joueur 1 VS Ordinateur", 0));
        pushButtonJ1J2->setText(QApplication::translate("DialogOption", "Joueur 1 VS JOueur 2", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogOption: public Ui_DialogOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOPTION_H
