/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelPlateau;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonThemes;
    QPushButton *pushButtonNewGameHaut;
    QPushButton *pushButtonOptions;
    QLabel *labelIconPlayer;
    QPushButton *pushButtonNewGame;
    QPushButton *pushButtonQuitter;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(492, 750);
        MainWindow->setMinimumSize(QSize(492, 698));
        MainWindow->setMaximumSize(QSize(1212121, 1212121));
        MainWindow->setMouseTracking(true);
        MainWindow->setStyleSheet(QStringLiteral("background-image: url(:/Images/mordor.jpg);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        labelPlateau = new QLabel(centralWidget);
        labelPlateau->setObjectName(QStringLiteral("labelPlateau"));
        labelPlateau->setGeometry(QRect(10, 110, 471, 471));
        labelPlateau->setMouseTracking(true);
        labelPlateau->setPixmap(QPixmap(QString::fromUtf8(":/Images/plateauHerbe.png")));
        labelPlateau->setScaledContents(true);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 60, 191, 41));
        label_2->setStyleSheet(QStringLiteral("color : #DDD;font: 63 italic 14pt 'URW Chancery L';background:rgba(0,0,0,0)"));
        label_2->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, -10, 491, 71));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonThemes = new QPushButton(layoutWidget);
        pushButtonThemes->setObjectName(QStringLiteral("pushButtonThemes"));
        pushButtonThemes->setMinimumSize(QSize(0, 50));
        pushButtonThemes->setFocusPolicy(Qt::NoFocus);
        pushButtonThemes->setLayoutDirection(Qt::LeftToRight);
        pushButtonThemes->setStyleSheet(QLatin1String("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.8, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color:black;\n"
"font: 63 italic 16pt"));
        pushButtonThemes->setAutoDefault(false);
        pushButtonThemes->setDefault(false);
        pushButtonThemes->setFlat(false);

        horizontalLayout->addWidget(pushButtonThemes);

        pushButtonNewGameHaut = new QPushButton(layoutWidget);
        pushButtonNewGameHaut->setObjectName(QStringLiteral("pushButtonNewGameHaut"));
        pushButtonNewGameHaut->setMinimumSize(QSize(0, 50));
        pushButtonNewGameHaut->setFocusPolicy(Qt::NoFocus);
        pushButtonNewGameHaut->setLayoutDirection(Qt::LeftToRight);
        pushButtonNewGameHaut->setStyleSheet(QLatin1String("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.8, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color:black;\n"
"font: 63 italic 16pt"));
        pushButtonNewGameHaut->setAutoDefault(false);
        pushButtonNewGameHaut->setDefault(false);
        pushButtonNewGameHaut->setFlat(false);

        horizontalLayout->addWidget(pushButtonNewGameHaut);

        pushButtonOptions = new QPushButton(layoutWidget);
        pushButtonOptions->setObjectName(QStringLiteral("pushButtonOptions"));
        pushButtonOptions->setMinimumSize(QSize(0, 50));
        pushButtonOptions->setFocusPolicy(Qt::NoFocus);
        pushButtonOptions->setLayoutDirection(Qt::LeftToRight);
        pushButtonOptions->setStyleSheet(QLatin1String("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.8, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));\n"
"color:black;\n"
"font: 63 italic 16pt"));
        pushButtonOptions->setAutoDefault(false);
        pushButtonOptions->setDefault(false);
        pushButtonOptions->setFlat(false);

        horizontalLayout->addWidget(pushButtonOptions);

        labelIconPlayer = new QLabel(centralWidget);
        labelIconPlayer->setObjectName(QStringLiteral("labelIconPlayer"));
        labelIconPlayer->setGeometry(QRect(290, 60, 91, 41));
        labelIconPlayer->setStyleSheet(QStringLiteral("color : #7C5A0D ;font: 63 italic 14pt 'URW Chancery L';background:rgba(0,0,0,0)"));
        labelIconPlayer->setAlignment(Qt::AlignCenter);
        pushButtonNewGame = new QPushButton(centralWidget);
        pushButtonNewGame->setObjectName(QStringLiteral("pushButtonNewGame"));
        pushButtonNewGame->setGeometry(QRect(31, 591, 440, 70));
        pushButtonNewGame->setMinimumSize(QSize(440, 70));
        pushButtonNewGame->setMaximumSize(QSize(440, 16777215));
        pushButtonNewGame->setFocusPolicy(Qt::StrongFocus);
        pushButtonNewGame->setLayoutDirection(Qt::LeftToRight);
        pushButtonNewGame->setStyleSheet(QLatin1String("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(50, 50, 50,255), stop:1 rgba(12, 165, 255, 255));\n"
"color:black;\n"
"font: 63 italic 18pt"));
        pushButtonNewGame->setAutoDefault(false);
        pushButtonNewGame->setDefault(false);
        pushButtonNewGame->setFlat(false);
        pushButtonQuitter = new QPushButton(centralWidget);
        pushButtonQuitter->setObjectName(QStringLiteral("pushButtonQuitter"));
        pushButtonQuitter->setGeometry(QRect(31, 667, 440, 70));
        pushButtonQuitter->setMinimumSize(QSize(440, 70));
        pushButtonQuitter->setMaximumSize(QSize(440, 16777215));
        pushButtonQuitter->setStyleSheet(QLatin1String("background:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(50, 50, 50,255), stop:1 rgba(12, 165, 255, 255));\n"
"color:black;\n"
"font: 63 italic 18pt"));
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        layoutWidget->raise();
        labelPlateau->raise();
        label_2->raise();
        labelIconPlayer->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "The Little Rocks game", 0));
        labelPlateau->setText(QString());
        label_2->setText(QString());
        pushButtonThemes->setText(QApplication::translate("MainWindow", "Themes", 0));
        pushButtonNewGameHaut->setText(QApplication::translate("MainWindow", "Nouvelle partie ", 0));
        pushButtonOptions->setText(QApplication::translate("MainWindow", "Options", 0));
        labelIconPlayer->setText(QString());
        pushButtonNewGame->setText(QApplication::translate("MainWindow", "Nouvelle partie ! ", 0));
        pushButtonQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
