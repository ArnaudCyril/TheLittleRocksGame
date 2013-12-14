/********************************************************************************
** Form generated from reading UI file 'dialogtheme.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTHEME_H
#define UI_DIALOGTHEME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogTheme
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonThemeBois;
    QPushButton *pushButtonThemeHerbe;
    QPushButton *pushButtonThemeNeon;
    QPushButton *pushButtonThemeMario;
    QPushButton *pushButtonThemeMinecraft;

    void setupUi(QDialog *DialogTheme)
    {
        if (DialogTheme->objectName().isEmpty())
            DialogTheme->setObjectName(QStringLiteral("DialogTheme"));
        DialogTheme->resize(368, 565);
        DialogTheme->setStyleSheet(QStringLiteral("background:#333;"));
        verticalLayout_2 = new QVBoxLayout(DialogTheme);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonThemeBois = new QPushButton(DialogTheme);
        pushButtonThemeBois->setObjectName(QStringLiteral("pushButtonThemeBois"));
        pushButtonThemeBois->setStyleSheet(QLatin1String("font: italic 20pt 'PMingLiU';\n"
"background:#BBB"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/plateau.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonThemeBois->setIcon(icon);
        pushButtonThemeBois->setIconSize(QSize(96, 96));

        verticalLayout->addWidget(pushButtonThemeBois);

        pushButtonThemeHerbe = new QPushButton(DialogTheme);
        pushButtonThemeHerbe->setObjectName(QStringLiteral("pushButtonThemeHerbe"));
        pushButtonThemeHerbe->setStyleSheet(QLatin1String("font: italic 20pt 'PMingLiU';\n"
"background:#BBB"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/plateauHerbe.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonThemeHerbe->setIcon(icon1);
        pushButtonThemeHerbe->setIconSize(QSize(96, 96));

        verticalLayout->addWidget(pushButtonThemeHerbe);

        pushButtonThemeNeon = new QPushButton(DialogTheme);
        pushButtonThemeNeon->setObjectName(QStringLiteral("pushButtonThemeNeon"));
        pushButtonThemeNeon->setStyleSheet(QLatin1String("font: italic 20pt 'PMingLiU';\n"
"background:#BBB"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/plateauNeon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonThemeNeon->setIcon(icon2);
        pushButtonThemeNeon->setIconSize(QSize(96, 96));

        verticalLayout->addWidget(pushButtonThemeNeon);

        pushButtonThemeMario = new QPushButton(DialogTheme);
        pushButtonThemeMario->setObjectName(QStringLiteral("pushButtonThemeMario"));
        pushButtonThemeMario->setStyleSheet(QLatin1String("font: italic 20pt 'PMingLiU';\n"
"background:#BBB"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/plateau-mario.gif"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonThemeMario->setIcon(icon3);
        pushButtonThemeMario->setIconSize(QSize(96, 96));

        verticalLayout->addWidget(pushButtonThemeMario);

        pushButtonThemeMinecraft = new QPushButton(DialogTheme);
        pushButtonThemeMinecraft->setObjectName(QStringLiteral("pushButtonThemeMinecraft"));
        pushButtonThemeMinecraft->setStyleSheet(QLatin1String("font: italic 20pt 'PMingLiU';\n"
"background:#BBB"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/craft"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonThemeMinecraft->setIcon(icon4);
        pushButtonThemeMinecraft->setIconSize(QSize(96, 96));

        verticalLayout->addWidget(pushButtonThemeMinecraft);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(DialogTheme);

        QMetaObject::connectSlotsByName(DialogTheme);
    } // setupUi

    void retranslateUi(QDialog *DialogTheme)
    {
        DialogTheme->setWindowTitle(QApplication::translate("DialogTheme", "Choix du Theme", 0));
        pushButtonThemeBois->setText(QApplication::translate("DialogTheme", "     Bois", 0));
        pushButtonThemeHerbe->setText(QApplication::translate("DialogTheme", "  Herbe", 0));
        pushButtonThemeNeon->setText(QApplication::translate("DialogTheme", "   Neon", 0));
        pushButtonThemeMario->setText(QApplication::translate("DialogTheme", "   Mario", 0));
        pushButtonThemeMinecraft->setText(QApplication::translate("DialogTheme", "Minecraft", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogTheme: public Ui_DialogTheme {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTHEME_H
