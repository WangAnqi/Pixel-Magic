/********************************************************************************
** Form generated from reading UI file 'pixel_magic.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIXEL_MAGIC_H
#define UI_PIXEL_MAGIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pixel_magicClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pixel_magicClass)
    {
        if (pixel_magicClass->objectName().isEmpty())
            pixel_magicClass->setObjectName(QStringLiteral("pixel_magicClass"));
        pixel_magicClass->resize(600, 400);
        menuBar = new QMenuBar(pixel_magicClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        pixel_magicClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pixel_magicClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        pixel_magicClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(pixel_magicClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pixel_magicClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(pixel_magicClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        pixel_magicClass->setStatusBar(statusBar);

        retranslateUi(pixel_magicClass);

        QMetaObject::connectSlotsByName(pixel_magicClass);
    } // setupUi

    void retranslateUi(QMainWindow *pixel_magicClass)
    {
        pixel_magicClass->setWindowTitle(QApplication::translate("pixel_magicClass", "pixel_magic", 0));
    } // retranslateUi

};

namespace Ui {
    class pixel_magicClass: public Ui_pixel_magicClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIXEL_MAGIC_H
